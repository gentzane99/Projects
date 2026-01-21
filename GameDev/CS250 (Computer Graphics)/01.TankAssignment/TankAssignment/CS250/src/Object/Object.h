/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Object.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #3
 \date    02/27/2020
 \brief   Object class declaration
******************************************************************************/
#pragma once

#include "Math/Matrix4.h"
#include "Math/Vertex.h"
#include "Parser/CS250Parser.h"
#include "Rasterizer/rasterizer.h"
#include "Camera/Camera.h"
#include <vector>

//Enum for the current camera mode
enum CameraMode { FirstPersonMode, ThirdPersonMode, RootedCameraMode };

class Object
{
	public:

		//Default constructor
		Object();

		//Render for the object
		void Render(sf::Image &, bool, CameraMode, Camera & );

		//Computes matrices
		void ModelToWorld();
		void CameraToProjectionWindow(Camera &);
		void ProjectionWindowToViewport(const int, const int);
		void ModelToViewport();
		void ParentModelToWorld(Matrix4 &);
		void GeneralRotationMethod(Camera &);

		//Getters
		Point4 & GetTranslation();
		Point4 & GetScale();
		float GetRotationX();
		float GetRotationY();
		float GetRotationZ();

		//Setters
		void SetTranslation(const Point4 &);
		void SetScale(const Point4 &);
		void SetRotation(const float, const float, const float);
		void SetParent(Object &);

		//Vector of vertices to store all the vertices
		std::vector<Rasterizer::Vertex> Vertices;	

	private:

		//Translation, scale and rotation of the object
		Point4 Translation;
		Point4 Scale;
		float RotationX;
		float RotationY;
		float RotationZ;

		//Variables to store the matrices
		Matrix4 ModelToWorldMatrix;
		Matrix4 WorldToCameraMatrix;
		Matrix4 CameraToProjectionWindowMatrix;
		Matrix4 ProjectionWindowToViewportMatrix;
		
		//Vector of vertices to save the vertices
		std::vector<Rasterizer::Vertex> SaveVertices;

		//Pointer to the objects parent
		Object * Parent;
};