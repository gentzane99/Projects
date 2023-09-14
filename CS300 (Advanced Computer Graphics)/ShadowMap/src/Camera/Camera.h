/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Camera.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #1
 \date    06/09/2020
 \brief   Camera class declaration
******************************************************************************/
#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
	public:

		//Constructor
		Camera();

		//View matrix update
		void UpdateView();

		//Getter camera up vector
		const glm::vec3 & GetCameraUp() const;

		//Getter camera right vector
		const glm::vec3 & GetCameraRight() const;

		//Getter camera front vector
		const glm::vec3 & GetCameraView() const;
	
		//Getter view matrix
		const glm::mat4 & GetView() const;

		//Getter Latitude
		float GetLatitude();

		//Getter Azimuth
		float GetAzimuth();

		//Getter Radius
		float GetRadius();

		//Setter camera up vector
		 void SetCameraUp(const glm::vec3 &);

		//Setter camera right vector
		 void SetCameraRight(const glm::vec3 &);

		//Setter camera front vector
		 void SetCameraView(const glm::vec3 &);

		//Setter view matrix
		 void SetView(const glm::mat4 &);

		 //Setter Latitude
		 void SetLatitude(const float);

		 //Setter Azimuth
		 void SetAzimuth(const float);

		 //Setter Radius
		 void SetRadius(const float);

		 //Get camera position
		 glm::vec3 GetCartesianPosition() const;

	private:

		glm::vec3 CameraUp;
		glm::vec3 CameraRight;
		glm::vec3 CameraView;

		float Latitude;
		float Azimuth;
		float Radius;

		glm::mat4 View;

};