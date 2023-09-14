/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Camera.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #1
 \date    06/09/2020
 \brief   Camera class declaration
******************************************************************************/
#include "Camera.h"
#include <SDL2/SDL.h>

//Variable for the pi value
const float pi = glm::pi<float>();

Camera::Camera() : CameraUp(0.0f, 1.0f, 0.0f), CameraView(0.0f, 0.0f, -1.0f), CameraRight(glm::vec3(glm::cross(CameraUp, CameraView))),
Latitude(pi/2.0f), Azimuth(pi/2.0f), Radius(50.0f), View(glm::lookAt(GetCartesianPosition(), glm::vec3(0.0f, 0.0f, 0.0f), CameraUp))
{}

void Camera::UpdateView()
{
	View = glm::lookAt(GetCartesianPosition(), glm::vec3(0.0f, 0.0f, 0.0f), CameraUp);
}

const glm::vec3 & Camera::GetCameraUp() const
{
	return CameraUp;
}

const glm::vec3 & Camera::GetCameraRight() const
{
	return CameraUp;
}

const glm::vec3 & Camera::GetCameraView() const
{
	return CameraView;
}

const glm::mat4 & Camera::GetView() const
{
	return View;
}

float Camera::GetLatitude()
{
	return Latitude;
}

float Camera::GetAzimuth()
{
	return Azimuth;
}

float Camera::GetRadius()
{
	return Radius;
}

void Camera::SetCameraUp(const glm::vec3 & up)
{
	CameraUp = up;
}

void Camera::SetCameraRight(const glm::vec3 & right)
{
	CameraRight = right;
}

void Camera::SetCameraView(const glm::vec3 & view)
{
	CameraView = view;
}

void Camera::SetView(const glm::mat4 & view)
{
	View = view;
}

void Camera::SetLatitude(const float latitude)
{
	if (latitude > pi || latitude < 0.0f)
		return;

	Latitude = latitude;
}

void Camera::SetAzimuth(const float azimuth)
{
	Azimuth = azimuth;
}

void Camera::SetRadius(const float radius)
{
	if (radius <= 0.5f)
		return;

	Radius = radius;
}

glm::vec3 Camera::GetCartesianPosition() const
{
	return glm::vec3(Radius * sinf(Latitude) * cosf(Azimuth),
			  	     Radius * cosf(Latitude),
					 Radius * sinf(Latitude) * sinf(Azimuth));
}
