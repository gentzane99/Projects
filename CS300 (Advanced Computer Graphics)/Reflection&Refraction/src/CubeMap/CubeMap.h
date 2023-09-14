/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    CubeMap.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #4
 \date    07/15/2020
 \brief   CubeMap class declaration
******************************************************************************/
#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


class CubeMap
{
	public:

		//Constructor for the cubemap 
		CubeMap();

		//Create the fbo 
		void FBOCube();

		//Load the textures of the skybox
		unsigned int LoadCubemap(std::vector<std::string> Faces);

		//Textures for the cubemap
		std::vector<std::string> FacesCubeMap
		{
			"Textures/CubeMap/CubeMap_Right.png",
			"Textures/CubeMap/CubeMap_Left.png",
			"Textures/CubeMap/CubeMap_Top.png",
			"Textures/CubeMap/CubeMap_Bottom.png",
			"Textures/CubeMap/CubeMap_Front.png",
			"Textures/CubeMap/CubeMap_Back.png"
		};

		std::vector<std::string> FacesCottonCandy
		{
			"Textures/CottonCandy/CottonCandy_Right.png",
			"Textures/CottonCandy/CottonCandy_Left.png",
			"Textures/CottonCandy/CottonCandy_Top.png",
			"Textures/CottonCandy/CottonCandy_Bottom.png",
			"Textures/CottonCandy/CottonCandy_Front.png",
			"Textures/CottonCandy/CottonCandy_Back.png"
		};

		GLuint cubemap;
		GLuint cubeFBO[6];
		float RefractionIndex;

		//Up and direction vectors of the faces
		std::vector<glm::vec3> Up;
		std::vector<glm::vec3> Front;
};