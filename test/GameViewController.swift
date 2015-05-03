//
//  GameViewController.swift
//  test
//
//  Created by Antoine Rached on 4/14/15.
//  Copyright (c) 2015 Antoine Rached. All rights reserved.
//

import UIKit
import QuartzCore
import SceneKit
import CoreMotion
class GameViewController: UIViewController,SCNSceneRendererDelegate {
    var cameraIndex:Int=0
    var sceneWrapper:SceneWrapper=SceneWrapper(fileName: "art.scnassets/racetrack/racetrack.dae",carFileNamed: "art.scnassets/car/car.dae")
    var leftView:SCNView?
    var rightView:SCNView?
    var motionManager:CMMotionManager = CMMotionManager()
    override func viewWillAppear(animated: Bool) {
        
        
        
        self.motionManager.deviceMotionUpdateInterval=1.0/40
        self.motionManager.startDeviceMotionUpdatesToQueue(NSOperationQueue(), withHandler:moveObjects)
    }
    func moveObjects(motion: CMDeviceMotion!, error: NSError!) {
        self.updateActiveCamera()
        self.updateCar()
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        self.initViews()
    }
    func initViews(){
        self.sceneWrapper.scene.background.contents=["right.jpg","left.jpg","top.jpg","bot.jpg","middle.jpg","back.jpg"]
        self.leftView=SCNView(frame:CGRectMake(0, 0, self.view.frame.size.width/2, self.view.frame.size.height))
        self.rightView=SCNView(frame: CGRectMake(self.view.frame.size.width/2, 0, self.view.frame.size.width/2, self.view.frame.size.height))
        
        self.leftView?.backgroundColor=UIColor.blueColor()
        self.rightView?.backgroundColor=UIColor.blueColor()
        
        let seperator=UIView(frame: CGRectMake(self.view.frame.size.width/2-1, 0, 2, self.view.frame.size.height))
        seperator.backgroundColor=UIColor.whiteColor()
            
        
        self.view.addSubview(self.leftView!)
        self.view.addSubview(self.rightView!)
        self.view.addSubview(seperator)
        
        self.leftView?.scene=sceneWrapper.scene
        self.rightView?.scene=sceneWrapper.scene
        
        self.leftView?.playing=true
        self.rightView?.playing=true
        
        self.leftView?.autoenablesDefaultLighting=false;
        self.rightView?.autoenablesDefaultLighting=false;
        
        self.leftView?.preferredFramesPerSecond=40
        self.rightView?.preferredFramesPerSecond=40
        
        self.leftView?.pointOfView=(sceneWrapper.camerasNodeArray.objectAtIndex(cameraIndex) as? StereoCameraNodeWrapper)?.leftLensNode
        self.rightView?.pointOfView=(sceneWrapper.camerasNodeArray.objectAtIndex(cameraIndex) as? StereoCameraNodeWrapper)?.rightLensNode
        
    }
    func updateCar(){
        update(0.2, 0.0, 1/40)
        
        self.sceneWrapper.translationNode.transform=SCNMatrix4MakeTranslation(getPosX(), getPosY(), getPosZ())
        NSLog("X:%f Z:%f",getPosX(),getPosZ())
        
        let m1=getBase(0)
        let sm1=SCNMatrix4(m11: m1.m11, m12: m1.m12, m13: m1.m13, m14: 0, m21: m1.m21, m22: m1.m22, m23: m1.m23, m24: 0, m31: m1.m31, m32: m1.m32, m33: m1.m33, m34: 0, m41: 0, m42: 0, m43: 0, m44: 1);
        
        

        
        let m2=getBase(2)
        let sm2=SCNMatrix4(m11: m2.m11, m12: m2.m12, m13: m2.m13, m14: 0, m21: m2.m21, m22: m2.m22, m23: m2.m23, m24: 0, m31: m2.m31, m32: m2.m32, m33: m2.m33, m34: 0, m41: 0, m42: 0, m43: 0, m44: 1);
        /*
        self.sceneWrapper.tire1.transform=SCNMatrix4MakeRotation(0.8, 0, 1, 0)
        
        let matrix=self.sceneWrapper.tire1.transform
        
        NSLog("\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f", matrix.m11,matrix.m12,matrix.m13,matrix.m14,matrix.m21,matrix.m22,matrix.m23,matrix.m24,matrix.m31,matrix.m32,matrix.m33,matrix.m34,matrix.m41,matrix.m42,matrix.m43,matrix.m44)
        */
        
        //self.sceneWrapper.rotationNode.transform=SCNMatrix4Rotate(self.sceneWrapper.rotationNode.transform, 0.005, 0, 1, 0);
        
        self.sceneWrapper.tire1.transform=SCNMatrix4Mult(sm1,self.sceneWrapper.tire1InitialMatrix)
        self.sceneWrapper.tire2.transform=SCNMatrix4Mult(sm1,self.sceneWrapper.tire2InitialMatrix)
        self.sceneWrapper.tire3.transform=SCNMatrix4Mult(sm2,self.sceneWrapper.tire3InitialMatrix)
        self.sceneWrapper.tire4.transform=SCNMatrix4Mult(sm2,self.sceneWrapper.tire4InitialMatrix)
        
    }
    func updateActiveCamera(){
        let rotationMatrix=self.motionManager.deviceMotion.attitude.rotationMatrix
        
        var matrix=SCNMatrix4(m11:Float(rotationMatrix.m11), m12:Float(rotationMatrix.m12), m13: Float(rotationMatrix.m13), m14: 0.0, m21:Float(rotationMatrix.m21), m22: Float(rotationMatrix.m22), m23: Float(rotationMatrix.m23), m24: 0.0, m31: Float(rotationMatrix.m31), m32: Float(rotationMatrix.m32), m33: Float(rotationMatrix.m33), m34: 0.0, m41: 0.0, m42: 0.0, m43: 0.0, m44: 1.0)
        
        var rotation=SCNMatrix4MakeRotation(-Float(M_PI_2), 0, 0, 1);
        matrix=SCNMatrix4Mult(rotation, matrix)
        matrix=SCNMatrix4Rotate(matrix, -Float(M_PI_2), 1, 0, 0)
        
        //NSLog("\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f", matrix.m11,matrix.m12,matrix.m13,matrix.m14,matrix.m21,matrix.m22,matrix.m23,matrix.m24,matrix.m31,matrix.m32,matrix.m33,matrix.m34,matrix.m41,matrix.m42,matrix.m43,matrix.m44)
        
        let activeCameraNode=(sceneWrapper.camerasNodeArray.objectAtIndex(cameraIndex) as? StereoCameraNodeWrapper)
        activeCameraNode?.mainNode.transform=SCNMatrix4Mult(matrix,activeCameraNode?.mainNodePosition as SCNMatrix4!)
        
    }
    override func motionBegan(motion: UIEventSubtype, withEvent event: UIEvent) {
        if(event.subtype == UIEventSubtype.MotionShake)
        {
            self.cameraIndex++
            self.cameraIndex=self.cameraIndex%self.sceneWrapper.camerasNodeArray.count
            self.leftView?.pointOfView=(sceneWrapper.camerasNodeArray.objectAtIndex(cameraIndex) as? StereoCameraNodeWrapper)?.leftLensNode
            self.rightView?.pointOfView=(sceneWrapper.camerasNodeArray.objectAtIndex(cameraIndex) as? StereoCameraNodeWrapper)?.rightLensNode
        }
    }
    override func shouldAutorotate() -> Bool {
        return true
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    override func supportedInterfaceOrientations() -> Int {
        if UIDevice.currentDevice().userInterfaceIdiom == .Phone {
            return Int(UIInterfaceOrientationMask.AllButUpsideDown.rawValue)
        } else {
            return Int(UIInterfaceOrientationMask.All.rawValue)
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Release any cached data, images, etc that aren't in use.
    }

}
