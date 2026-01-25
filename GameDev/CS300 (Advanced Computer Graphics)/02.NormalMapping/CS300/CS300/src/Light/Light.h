/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Light.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #1
 \date    06/09/2020
 \brief   Light and Material class declaration
******************************************************************************/
#pragma once

#include <glm/gtc/matrix_transform.hpp>

struct Light
{
	glm::vec3 AmbientLight = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 DiffuseLight = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 SpecularLight = glm::vec3(1.0f, 1.0f, 1.0f);

	float InnerAngle = 10.0f;
	float OuterAngle = 30.0f;

	float FallOff = 3.0f;
	float AttenuationC1 = 0.0f;
	float AttenuationC2 = 0.0f;
	float AttenuationC3 = 0.001f;

	bool PointLight = true;
	bool SpotLight = false;
	bool DirectionalLight = false;
};

struct Material
{
	glm::vec3 AmbientMaterial = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 DiffuseMaterial = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 SpecularMaterial = glm::vec3(0.5f, 0.5f, 0.5f);
	float ShininessMaterial = 15.0f;
};