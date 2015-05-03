//
//  StereoCameraNodeWrapper.swift
//  carSimulation
//
//  Created by Antoine Rached on 3/16/15.
//  Copyright (c) 2015 Antoine Rached. All rights reserved.
//

import Foundation
import SceneKit
class StereoCameraNodeWrapper{
    var mainNode:SCNNode
    var mainNodePosition:SCNMatrix4
    var leftLensNode:SCNNode
    var rightLensNode:SCNNode
    init(mainNode:SCNNode,interAxialDistance:Float,zFar:Double,zNear:Double){
        self.mainNodePosition=mainNode.transform
        self.mainNode=mainNode
        self.leftLensNode=SCNNode()
        self.leftLensNode.transform=SCNMatrix4MakeTranslation(-interAxialDistance/2, 0, 0)
        self.mainNode.addChildNode(self.leftLensNode)
        self.rightLensNode=SCNNode()
        self.rightLensNode.transform=SCNMatrix4MakeTranslation(interAxialDistance/2, 0, 0)
        self.mainNode.addChildNode(self.rightLensNode)
        self.leftLensNode.camera=SCNCamera()
        self.rightLensNode.camera=SCNCamera()
        self.leftLensNode.camera?.zFar=zFar
        self.rightLensNode.camera?.zFar=zFar
        self.leftLensNode.camera?.zNear=zNear
        self.rightLensNode.camera?.zNear=zNear
    }
    
}