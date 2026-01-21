/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Camera.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #3
 \date    02/27/2020
 \brief   Function definitions for Camera class.
******************************************************************************/

#include "Camera/Camera.h"

//Camera default constructor
Camera::Camera() : COP(Point4()), ViewVector(Vector4()), UpVector(Vector4()), RightVector(Vector4()), 
				   FocalLength(0), Left(0), Right(0), Top(0), Bottom(0), NearPlane(0), FarPlane(0) {}


//Setters

void Camera::SetCOP(const Point4 & COP_)
{
	COP = COP_;
}

void Camera::SetViewVector(const Vector4 & ViewVector_)
{
	ViewVector = ViewVector_;
}

void Camera::SetUpVector(const Vector4 & UpVector_)
{
	UpVector = UpVector_;
}

void Camera::SetRightVector(const Vector4 & RightVector_)
{
	RightVector = RightVector_;
}

void Camera::SetFocalLength(float FocalLenght_)
{
	FocalLength = FocalLenght_;
}

void Camera::SetRight(float Right_)
{
	Right = Right_;
}

void Camera::SetLeft(float Left_)
{
	Left = Left_;
}

void Camera::SetTop(float Top_)
{
	Top = Top_;
}

void Camera::SetBottom(float Bottom_)
{
	Bottom = Bottom_;
}

void Camera::SetNearPlane(float NearPlane_)
{
	NearPlane = NearPlane_;
}

void Camera::SetFarPlane(float FarPlane_)
{
	FarPlane = FarPlane_;
}

//Getters

const Point4 & Camera::GetCOP()
{
	return COP;
}

const Vector4 & Camera::GetViewVector()
{
	return ViewVector;
}

const Vector4 & Camera::GetUpVector()
{
	return UpVector;
}

const Vector4 & Camera::GetRightVector()
{
	return RightVector;
}

float Camera::GetFocalLength()
{
	return FocalLength;
}

float Camera::GetRight()
{
	return Right;
}

float Camera::GetLeft()
{
	return Left;
}

float Camera::GetTop()
{
	return Top;
}

float Camera::GetBottom()
{
	return Bottom;
}

float Camera::GetNearPlane()
{
	return NearPlane;
}

float Camera::GetFarPlane()
{
	return FarPlane;
}
