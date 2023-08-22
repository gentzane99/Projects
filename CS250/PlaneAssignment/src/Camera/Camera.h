/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Camera.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #3
 \date    02/27/2020
 \brief   Function declaration for Camera class.
******************************************************************************/
#pragma once

#include "Math/Point4.h"
#include "Parser/CS250Parser.h"

class Camera
{
	public:

		//Default constructor
		Camera();

		//Setters
		void SetCOP(const Point4 &);
		void SetViewVector(const Vector4 &);
		void SetUpVector(const Vector4 &);
		void SetRightVector(const Vector4 &);
		void SetFocalLength(float);
		void SetRight(float);
		void SetLeft(float);
		void SetTop(float);
		void SetBottom(float);
		void SetNearPlane(float);
		void SetFarPlane(float);

		//Getters
		const Point4  & GetCOP();
		const Vector4 & GetViewVector();
		const Vector4 & GetUpVector();
		const Vector4 & GetRightVector();
		float GetFocalLength();
		float GetRight();
		float GetLeft();
		float GetTop();
		float GetBottom();
		float GetNearPlane();
		float GetFarPlane();

	private:

		//Variables for the camera
		Point4 COP;
		Vector4 ViewVector;
		Vector4 UpVector;
		Vector4 RightVector;
		float FocalLength;
		float Left;
		float Right;
		float Top;
		float Bottom;
		float NearPlane;
		float FarPlane;
};