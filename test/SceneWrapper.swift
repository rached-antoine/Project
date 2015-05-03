//
//  GameScene.swift
//  carSimulation
//
//  Created by Antoine Rached on 3/16/15.
//  Copyright (c) 2015 Antoine Rached. All rights reserved.
//

import Foundation
import SceneKit
class SceneWrapper{
    
    var scene:SCNScene
    
    var startingPositionNode:SCNNode
    var translationNode:SCNNode
    var rotationNode:SCNNode
    
    var tire1:SCNNode
    var tire2:SCNNode
    var tire3:SCNNode
    var tire4:SCNNode
    
    var tire1InitialMatrix:SCNMatrix4
    var tire2InitialMatrix:SCNMatrix4
    var tire3InitialMatrix:SCNMatrix4
    var tire4InitialMatrix:SCNMatrix4
    
    var camerasNodeArray:NSMutableArray

    init(fileName:String, carFileNamed:String){
        
        self.scene=SCNScene(named: fileName)!
        self.startingPositionNode=self.scene.rootNode.childNodeWithName("startingPosition", recursively: true)!
        
        let s=SCNScene(named: carFileNamed)
        
        let carNode=s?.rootNode.childNodeWithName("gPoint", recursively: true)
        self.startingPositionNode.addChildNode(carNode as SCNNode!)
        
        
        self.translationNode=self.scene.rootNode.childNodeWithName("translationNode", recursively: true)!
        self.rotationNode=self.scene.rootNode.childNodeWithName("rotationNode", recursively: true)!
        
        self.tire1=self.scene.rootNode.childNodeWithName("tire1", recursively: true)!
        self.tire2=self.scene.rootNode.childNodeWithName("tire2", recursively: true)!
        self.tire3=self.scene.rootNode.childNodeWithName("tire3", recursively: true)!
        self.tire4=self.scene.rootNode.childNodeWithName("tire4", recursively: true)!
        
        self.tire1InitialMatrix=self.tire1.transform
        self.tire2InitialMatrix=self.tire2.transform
        self.tire3InitialMatrix=self.tire3.transform
        self.tire4InitialMatrix=self.tire4.transform

        
        self.camerasNodeArray=NSMutableArray()
        initCameraArray()
    }
    
    
    func initCameraArray(){
        
        let array=self.scene.rootNode.childNodesPassingTest({(node, stop) -> Bool in
            if(node.camera != nil){
                return true;
            }
            else{
                return false;
            }
        })
        if(array.count==0){
            NSException(name: "NoCamera", reason: "No camera with adequat name has been found", userInfo: nil).raise()
        }
        
        for(var i=0;i<array.count;++i){
            self.camerasNodeArray.addObject(StereoCameraNodeWrapper(mainNode: array[i] as SCNNode, interAxialDistance: 0.07, zFar: 400,zNear:0.001))
            
        }
    }

}