Assignment 2 | Normal Mapping

/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen 
Institute of Technology is prohibited.
Project: cs300_gentzane.pastor_2
Author: Gentzane Pastor gentzane.pastor 54000217
Creation date: 06/22/2020
----------------------------------------------------------------------------------------------------------*/

•How to run your program: Visual Studio 2017, Release x86 

• How to use your program:

- Move the camera around in always looking at the object.
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

- Select the light types:
	▪ 7: All lights become point lights.
	▪ 8: All lights become spot lights.
	▪ 9: All lights become directional lights.

	▪ P: Toggle to pause/start the light animation.
	▪ N: Toggle normal rendering
	▪ F: Toggle face/averaged normal
	▪ M: Toggle wireframe mode on/off

- T: Change between rendering modes:
	▪ Normal Mapping: Scene with lighting and normal mapping with texture
	▪ Normals: Geometry normal in camera space as color
	▪ Tangent: Geometry tangent in camera space as color
	▪ Bitangent: Geometry bitangent in camera space as color

- Object rotation for center shape.
	▪ Arrows Up/Down: Rotate the shape along Y-axis
	▪ Arrows Right/Left: Rotate the shape along X-axis

• Important parts of the code: 

vertex.vs, fragnment.fs, main.cpp, object.cpp

• Known issues and problems: 

