/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    ShadowMap.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #3
 \date    07/06/2020
 \brief  ShadowMap class declaration
******************************************************************************/
#pragma once
#include <GL/glew.h>

struct ShadowMap
{
	//Set the frame buffer
	void setupFBO(GLsizei, GLsizei);

	//Create the shadowmap quad
	void CreadShadowMapQuad();

	//Shadow map dimensions
	const unsigned int shadowMapWidth = 300;
	const unsigned int shadowMapHeight = 300;

	//Shadow FrameBuffer
	GLuint shadowFBO;

	//Depth texture
	GLuint depthTex;

	//Shadow map VAO and VBO
	GLuint QuadVAO = 0;
	GLuint QuadVBO;
};