Assignment 0 | Shape Library
Assignment 1 | Phong Illumination Model

/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen 
Institute of Technology is prohibited.
Project: cs300_gentzane.pastor_1
Author: Gentzane Pastor gentzane.pastor 54000217
Creation date: 07/10/2020
----------------------------------------------------------------------------------------------------------*/

•How to run your program: Visual Studio 2017, Release x86 

• How to use your program:

   Select shape to be rendered through the number keys.
    o	Numbers 1 to 5: Change the shape to be rendered
        1: Plane
        2: Cube
        3: Cone
        4: Cylinder
        5: Sphere
	+: Increase the shape subdivisions
	-: Decrease the shape subdivisions
        
	P: Toggle to pause/start the light animation. 
	N: Toggle normal rendering
	T: Toggle texture-mapping on/off
	F: Toggle face/averaged normal
	M: Toggle wireframe mode on/off

  Object rotation for center shape.
    o	Arrows Up/Down: Rotate the shape along Y-axis
    o	Arrows Right/Left: Rotate the shape along X-axis
    
  Move the camera around in always looking at the object. 
    o	W: Move up. 
    o	S: Move down.
    o	A: Move left. 
    o	D: Move right. 
    o	E: Further from object. 
    o	Q: Closer to object. 

  Select the light types: 
    o	7: All lights become point lights. 
    o	8: All lights become spot lights.
    o	9: All lights become directional lights. 

• Important parts of the code: 

vertex.vs, fragnment.fs, camera.cpp, main.cpp() 

• Known issues and problems:

