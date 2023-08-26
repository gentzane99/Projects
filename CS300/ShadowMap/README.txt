Assignment 3 | Shadow Mapping with PCF

/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen 
Institute of Technology is prohibited.
Project: cs300_gentzane.pastor_3
Author: Gentzane Pastor gentzane.pastor 54000217
Creation date: 07/06/2020
----------------------------------------------------------------------------------------------------------*/

•How to run your program: Visual Studio 2017, Release x86 

• How to use your program:

▪ Move the camera around in always looking at the object.
    ▪ W: Move up.
    ▪ S: Move down.
    ▪ A: Move left.
    ▪ D: Move right.
    ▪ E: Further from object.
    ▪ Q: Closer to object.
▪ Select shape to be rendered through the number keys.
    ▪ Numbers 1 to 5: Change the shape to be rendered
        – 1: Plane
        – 2: Cube
        – 3: Cone
        – 4: Cylinder
        – 5: Sphere

    ▪ +: Increase the shape subdivisions
    ▪ -: Decrease the shape subdivisions

▪ P: Toggle to pause/start the light animation.
▪ O: Toggle to pause/start adjacent object animation.
▪ N: Toggle normal rendering
▪ F: Toggle face/averaged normal
▪ M: Toggle wireframe mode on/off

▪ Object rotation for center shape.
    ▪ Arrows Up/Down: Rotate the shape along Y-axis
    ▪ Arrows Right/Left: Rotate the shape along X-axis

• Important parts of the code: 

ShadowMap.h/.cpp, shaders, main.cpp(Render)

• Known issues and problems: 
