Assignment 4 | Reflection and Refraction with Cube Mapping

/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen 
Institute of Technology is prohibited.
Project: cs300_gentzane.pastor_4
Author: Gentzane Pastor gentzane.pastor 54000217
Creation date: 07/17/2020
----------------------------------------------------------------------------------------------------------*/

•How to run your program: Visual Studio 2017, Release x86 

• How to use your program:

	-Move the camera around in always looking at the object.
		▪ W: Move up.
		▪ S: Move down.
		▪ A: Move left.
		▪ D: Move right.
		▪ E: Further from object.
		▪ Q: Closer to object.

	-Select shape to be rendered through the number keys.
	▪ Numbers 1 to 5: Change the shape to be rendered
		– 1: Plane
		– 2: Cube
		– 3: Cone
		– 4: Cylinder
		– 5: Sphere
	▪ +: Increase the shape subdivisions
	▪ -: Decrease the shape subdivisions

	- O: Toggle to pause/start adjacent object animation.
	- F: Toggle face/averaged normal
	- M: Toggle wireframe mode on/off
	- T: Cycle between the different modes (texture/ reflective/ refractive)
	- Z: Cubemap textures
	- X: Cotton candy textures
	- Object rotation for center shape.
		▪ Arrows Up/Down: Rotate the shape along Y-axis
		▪ Arrows Right/Left: Rotate the shape along X-axis

• Important parts of the code: 

CubeMap.cpp, main.cpp(Render function), CubeMap.fs/vs, vertex.vs and fragment.fs

• Known issues and problems: 
