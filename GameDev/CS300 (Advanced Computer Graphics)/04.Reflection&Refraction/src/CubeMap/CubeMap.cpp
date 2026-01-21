/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    CubeMap.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #4
 \date    07/15/2020
 \brief   Cubemap class functions definitions
******************************************************************************/
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "CubeMap.h"

CubeMap::CubeMap(): RefractionIndex(1.33f) 
{
	Up.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	Up.push_back(glm::vec3(0.0f, -1.0f, 0.0f));	
	Up.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	Up.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	Up.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	Up.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	Front.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	Front.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	Front.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	Front.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	Front.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	Front.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
}

void CubeMap::FBOCube()
{
	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	const unsigned EnvMapSize = 512;
	for (GLuint i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, EnvMapSize, EnvMapSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	// Create and set up the FBO
	glGenFramebuffers(6, cubeFBO);
	for (GLuint i = 0; i < 6; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, cubeFBO[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap, 0);
		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int CubeMap::LoadCubemap(std::vector<std::string> Faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int Width;
	int Height;
	int Channels;

	for (GLuint i = 0; i < Faces.size(); i++)
	{
		unsigned char * data = stbi_load(Faces[i].c_str(), &Width, &Height, &Channels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		else
		{
			//std::cout << "Cubemap texture failed on for face: " << Faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}