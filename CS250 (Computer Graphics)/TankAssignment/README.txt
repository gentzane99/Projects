Assignment 2: Simple Perspective Projection & Transformation
Assignment 3: Viewing Matrix using General Rotation Method

/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen 
Institute of Technology is prohibited.
Project: cs250_gentzane.pastor_3
Author: Gentzane Pastor, gentzane.pastor, 540000217
Creation date: 02/27/2020
----------------------------------------------------------------------------------------------------------*/
• How to run your program: Visual Studio 2017, Debug x86 
(It could be executed in Debug or Release and in any platform)

• How to use your program: 

	1: wireframe mode  
	2: solid mode  
	3: first person mode  
	4: third person mode  
	5: rooted camera mode  
	a: Rotates tank body/Right rotation(ccw) 
	d: Rotates tank body/Left rotation (cw) 
	q: Rotates turret/Left rotation (ccw) 
	e: Rotates turret/Right rotation (cw) 
	r: Rotates gun/Up rotation (cw) 
	f: Rotates gun/Down rotation (ccw)
	space: Move tank body forward 
	z: Decrease camera distance 
	x: Increase camera distance  
	h: Decrease camera height  
	y: Increase camera height 
	
• Important parts of the code: Matrices in Object.cpp and camera position and vector in main.cpp.
• Known issues and problems: Even though I think that I'm updating well the camera position and vectors
there is some bug when rotating the tank or the turret that makes the image to deform.