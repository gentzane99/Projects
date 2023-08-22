/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Object.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #3
 \date    02/27/2020
 \brief   Object class functions definitions
******************************************************************************/

#include "Object.h"
#include <algorithm>

/*!****************************************************************************
 \brief Object default constructor
******************************************************************************/
Object::Object(): Translation(Point4()), Scale(Point4()), RotationX(0), 
				  RotationY(0), RotationZ(0), Vertices(0), Parent(nullptr){}

/*!****************************************************************************
 \brief Renders the object
 \param sf::Image & - Reference to the image created in main
 \param bool - Determines if the Wireframe mode is on or not
 \param CameraMode - Determines the camera mode
 \param camera_ - Reference to the current camera
******************************************************************************/
void Object::Render(sf::Image & image, bool Wireframe_, CameraMode cameramode, Camera & camera_)
{
	//Computes the model to world
	ModelToWorld();

	//Computes the model to world
	GeneralRotationMethod(camera_);

	//Vector of vertices to save the vertices
	std::vector<Rasterizer::Vertex> SaveVertices2;

	//Saves the current vertices
	SaveVertices2 = Vertices;

	//Goes through all the vertices
	for (unsigned i = 0; i < SaveVertices2.size(); i += 3)
	{
		//Concatenates the model to world and the world to camera matrices multiplying 3 vertices
		SaveVertices2[i].mPosition = WorldToCameraMatrix * ModelToWorldMatrix * SaveVertices2[i].mPosition;
		SaveVertices2[i + 1].mPosition = WorldToCameraMatrix * ModelToWorldMatrix * SaveVertices2[i + 1].mPosition;
		SaveVertices2[i + 2].mPosition = WorldToCameraMatrix * ModelToWorldMatrix * SaveVertices2[i + 2].mPosition;

		//Checks if the points are smaller tham the nearplane
		if (SaveVertices2[i].mPosition.z <= -camera_.GetNearPlane() && SaveVertices2[i + 1].mPosition.z <= -camera_.GetNearPlane() && SaveVertices2[i + 2].mPosition.z <= -camera_.GetNearPlane())
		{ 
			//Saves the valid vertices
			SaveVertices.push_back(SaveVertices2[i]);
			SaveVertices.push_back(SaveVertices2[i + 1]);
			SaveVertices.push_back(SaveVertices2[i + 2]);
		}
	}

	//Computes the model to viewport
	ModelToViewport();

	//Checks it the Wireframe is false
	if (!Wireframe_)
	{
		//Goes through all the vertices
		for (unsigned i = 0; i < SaveVertices.size(); i += 3)
		{
			//Drawsthe triangles with three points
			DrawTriangleSolid(
				Point2D(SaveVertices[i].mPosition.x, SaveVertices[i].mPosition.y,
					   SaveVertices[i].mColor.r, SaveVertices[i].mColor.g, SaveVertices[i].mColor.b),
				Point2D(SaveVertices[i + 1].mPosition.x, SaveVertices[i + 1].mPosition.y,
					   SaveVertices[i + 1].mColor.r, SaveVertices[i + 1].mColor.g, SaveVertices[i + 1].mColor.b),
				Point2D(SaveVertices[i + 2].mPosition.x, SaveVertices[i + 2].mPosition.y,
					   SaveVertices[i + 2].mColor.r, SaveVertices[i + 2].mColor.g, SaveVertices[i + 2].mColor.b), image);
		}
	}

	//Checks it the Wireframe is true
	else
	{
		//Goes through all the vertices
		for (unsigned i = 0; i < SaveVertices.size(); i += 3)
		{
			//Draws a line between the first and the second point for the first side of the triangle
			DrawMidpointLine(
				Point2D(SaveVertices[i].mPosition.x, SaveVertices[i].mPosition.y,
					   SaveVertices[i].mColor.r, SaveVertices[i].mColor.g, SaveVertices[i].mColor.b),
				Point2D(SaveVertices[i + 1].mPosition.x, SaveVertices[i + 1].mPosition.y, 
					   SaveVertices[i + 1].mColor.r, SaveVertices[i + 1].mColor.g, SaveVertices[i + 1].mColor.b), image);
			
			//Draws a line between the second and the third point for the second side of the triangle
			DrawMidpointLine(
				Point2D(SaveVertices[i + 1].mPosition.x, SaveVertices[i + 1].mPosition.y, 
					    SaveVertices[i + 1].mColor.r, SaveVertices[i + 1].mColor.g, SaveVertices[i + 1].mColor.b),
				Point2D(SaveVertices[i + 2].mPosition.x, SaveVertices[i + 2].mPosition.y, 
					    SaveVertices[i + 2].mColor.r, SaveVertices[i + 2].mColor.g, SaveVertices[i + 2].mColor.b), image);
			
			//Draws a line between the third and the first point for the third side of the triangle
			DrawMidpointLine(
				Point2D(SaveVertices[i + 2].mPosition.x, SaveVertices[i + 2].mPosition.y, 
					    SaveVertices[i + 2].mColor.r, SaveVertices[i + 2].mColor.g, SaveVertices[i + 2].mColor.b),
				Point2D(SaveVertices[i].mPosition.x, SaveVertices[i].mPosition.y, 
					   SaveVertices[i].mColor.r, SaveVertices[i].mColor.g, SaveVertices[i].mColor.b), image);
		}
	}

	//Clears the vector of vertices
	SaveVertices.clear();
}

/*!****************************************************************************
 \brief Computes the model to world matrix
******************************************************************************/
void Object::ModelToWorld()
{
	//Creates a Matrix to save the parent matrix
	Matrix4 Save;

	//Sets it as the identity
	Save.Identity();

	//Calss the ParentModelToWorld function
	ParentModelToWorld(Save);

	//Computes the translation matrix
	Matrix4 TranslationMatrix = Matrix4(1, 0, 0, Translation.x,
										0, 1, 0 , Translation.y,
										0, 0, 1, Translation.z,
										0, 0, 0 , 1);

	//Computes the scale matrix
	Matrix4 ScaleMatrix = Matrix4(Scale.x, 0, 0, 0,
								  0, Scale.y, 0, 0,
								  0, 0, Scale.z, 0,
								  0, 0, 0, 1);

	//Computes the rotation matrix on x
	Matrix4 RotationMatrixX = Matrix4(1, 0, 0, 0,
									  0, cos(RotationX), -sin(RotationX), 0,
									  0, sin(RotationX), cos(RotationX), 0,
									  0, 0, 0, 1);

	//Computes the rotation matrix on y
	Matrix4 RotationMatrixY = Matrix4(cos(RotationY), 0, sin(RotationY), 0,
									  0, 1, 0, 0,
									 -sin(RotationY), 0, cos(RotationY), 0,
									  0, 0, 0, 1);

	//Computes the rotation matrix on z
	Matrix4 RotationMatrixZ = Matrix4(cos(RotationZ), -sin(RotationZ), 0, 0,
									 sin(RotationZ), cos(RotationZ), 0, 0,
									  0, 0, 1, 0,
									  0, 0, 0, 1);

	//Computes the matrix for all the rotation
	Matrix4 RotationMatrix = RotationMatrixX * RotationMatrixY * RotationMatrixZ;

	//Computes the model to world matrix
	ModelToWorldMatrix = Save * TranslationMatrix * RotationMatrix * ScaleMatrix;
}

/*!****************************************************************************
 \brief Computes the World to window matrix
 \param camera_ - Reference to the current camera
******************************************************************************/
void Object::CameraToProjectionWindow(Camera & camera_)
{
	CameraToProjectionWindowMatrix = Matrix4(camera_.GetFocalLength()/(camera_.GetRight() - camera_.GetLeft()), 0, 0, 0,
											0, camera_.GetFocalLength() / (camera_.GetTop() - camera_.GetBottom()), 0, 0,
											0, 0, -(camera_.GetFarPlane() + camera_.GetNearPlane())/
													(camera_.GetFarPlane() - camera_.GetNearPlane()), -2*(camera_.GetNearPlane() * camera_.GetFarPlane()) /
																										(camera_.GetFarPlane() - camera_.GetNearPlane()),
											0, 0, -1, 0);
}

/*!****************************************************************************
 \brief Computes the window to viewport
 \param const int - Width of the viewport
\param const int - Height of the viewport
******************************************************************************/
void Object::ProjectionWindowToViewport(const int Width_, const int Height_)
{
	ProjectionWindowToViewportMatrix = Matrix4((float)Width_ / 2, 0, 0, (float)Width_ / 2,
	0, (float)-Height_ / 2, 0, (float)Height_ / 2,
	0, 0, 1, 0,
	0, 0, 0, 1);
}

/*!****************************************************************************
 \brief Computes the model to viewport
******************************************************************************/
void Object::ModelToViewport()
{

	//Goes through all the vertices
	for (unsigned i = 0; i < SaveVertices.size(); i++)
	{
		//Computes the camera to projection window matrix for the vertices
		SaveVertices[i].mPosition = CameraToProjectionWindowMatrix * SaveVertices[i].mPosition;
	}
	
	//Goes through all the vertices
	for (unsigned i = 0; i < SaveVertices.size(); i++)
	{
		//Computes the perspective division
		SaveVertices[i].mPosition.x = SaveVertices[i].mPosition.x / SaveVertices[i].mPosition.w;
		SaveVertices[i].mPosition.y = SaveVertices[i].mPosition.y / SaveVertices[i].mPosition.w;
		SaveVertices[i].mPosition.z = SaveVertices[i].mPosition.z / SaveVertices[i].mPosition.w;
		SaveVertices[i].mPosition.w = SaveVertices[i].mPosition.w / SaveVertices[i].mPosition.w;
	}

	//Goes through all the vertices
	for (unsigned i = 0; i < SaveVertices.size(); i++)
	{
		//Multiplies the Window to viewport matrix with the vertices
		SaveVertices[i].mPosition = ProjectionWindowToViewportMatrix * SaveVertices[i].mPosition;
	}
}

/*!****************************************************************************
 \brief Computes the parent model to world matrix
 \param Matrix4 & - Reference to the matrix of parents model to world
******************************************************************************/
void Object::ParentModelToWorld(Matrix4 & ParentModelToWorldMatrix)
{
	//Checks if the object has a parent
	if (Parent)
	{
		//Computes the translation of the parent
		Matrix4 ParentTranslationMatrix = Matrix4(1, 0, 0, Parent->Translation.x,
			0, 1, 0, Parent->Translation.y,
			0, 0, 1, Parent->Translation.z,
			0, 0, 0, 1);

		//Computes the rotation on x of the parent
		Matrix4 ParentRotationMatrixX = Matrix4(1, 0, 0, 0,
			0, cos(Parent->RotationX), -sin(Parent->RotationX), 0,
			0, sin(Parent->RotationX), cos(Parent->RotationX), 0,
			0, 0, 0, 1);

		//Computes the rotation on y of the parent
		Matrix4 ParentRotationMatrixY = Matrix4(cos(Parent->RotationY), 0, sin(Parent->RotationY), 0,
			0, 1, 0, 0,
			-sin(Parent->RotationY), 0, cos(Parent->RotationY), 0,
			0, 0, 0, 1);

		//Computes the rotation on z of the parent
		Matrix4 ParentRotationMatrixZ = Matrix4(cos(Parent->RotationZ), -sin(Parent->RotationZ), 0, 0,
			sin(Parent->RotationZ), cos(Parent->RotationZ), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		//Computes the rotation matrix of al the rotations
		Matrix4 ParentRotationMatrix = ParentRotationMatrixX * ParentRotationMatrixY * ParentRotationMatrixZ;

		//Computes the model to world of the parent matrix
		ParentModelToWorldMatrix = ParentTranslationMatrix * ParentRotationMatrix * ParentModelToWorldMatrix;

		//Calls the parents ParentModelToWorld fuction in case the parent also has parents
		Parent->ParentModelToWorld(ParentModelToWorldMatrix);
	}	
}

/*!****************************************************************************
 \brief Computes the world to camera
 \param camera_ - Reference to the current camera
******************************************************************************/
void Object::GeneralRotationMethod(Camera & camera_)
{

	//Setp 1
	Matrix4 TCOP = Matrix4(1, 0, 0, -camera_.GetCOP().x,
		0, 1, 0, -camera_.GetCOP().y,
		0, 0, 1, -camera_.GetCOP().z,
		0, 0, 0, 1);

	//Step 2


	float vx = camera_.GetViewVector().x;
	float vy = camera_.GetViewVector().y;
	float vz = camera_.GetViewVector().z;

	float CosAngle = -vz / sqrtf(vx * vx + vz * vz);

	float SinAngle = vx / sqrtf(vx * vx + vz * vz);

	Matrix4 Ry = Matrix4(CosAngle, 0, SinAngle, 0,
						0, 1, 0, 0,
						-SinAngle, 0, CosAngle, 0,
						0, 0, 0, 1);

	//Step 3

	float CosAngle2 = sqrtf(vx * vx + vz * vz) / sqrtf(vx * vx + vy * vy + vz * vz);
	float SinAngle2 = -vy / sqrtf(vx * vx + vy * vy + vz * vz);

	Matrix4 Rx = Matrix4(1, 0, 0, 0,
						0, CosAngle2, -SinAngle2, 0,
						0, SinAngle2, CosAngle, 0,
						0, 0, 0, 1);

	//Step 4

	Vector4 UpVector2 = Rx * Ry * TCOP * camera_.GetUpVector();

	float ux = UpVector2.x;
	float uy = UpVector2.y;
	float uz = UpVector2.z;

	float CosAngle3 = uy /  sqrtf(uy * uy + ux * ux);

	float SinAngle3 = ux / sqrtf(uy * uy + ux * ux);

	Matrix4 Rz = Matrix4(CosAngle3, -SinAngle3, 0, 0,
						SinAngle3, CosAngle3, 0, 0,
					     0, 0, 1, 0,
					     0, 0, 0, 1);


	//Computes the world to camera matrix
	WorldToCameraMatrix = Rz * Rx * Ry * TCOP;

}
/*!****************************************************************************
 \brief Translation getter
 \return Point4 & - Reference to the translation
******************************************************************************/
Point4 & Object::GetTranslation()
{
	return Translation;
}

/*!****************************************************************************
 \brief Scale getter
 \return Point4 & -  Reference to the scale
******************************************************************************/
Point4 & Object::GetScale()
{
	return Scale;
}

/*!****************************************************************************
 \brief Rotation on x getter
 \return float - Rotation on x axis
******************************************************************************/
float Object::GetRotationX() 
{
	return RotationX;
}

/*!****************************************************************************
 \brief Rotation on z getter
 \return float - Rotation on x axis
******************************************************************************/
float Object::GetRotationY() 
{
	return RotationY;
}

/*!****************************************************************************
 \brief Rotation on z getter
 \return float - Rotation on z axis
******************************************************************************/
float Object::GetRotationZ()
{
	return RotationZ;
}

/*!****************************************************************************
 \brief Translation setter
 \param const Point4 & - Reference to the translation
******************************************************************************/
void Object::SetTranslation(const Point4 & Translation_)
{
	Translation = Translation_;
}

/*!****************************************************************************
 \brief Scale setter
 \param const Point4 & - Reference to the scale
******************************************************************************/
void Object::SetScale(const Point4 & Scale_)
{
	Scale = Scale_;
}

/*!****************************************************************************
 \brief Rotations setter
 \param const float - Rotation on x
 \param const float - Rotation on y
 \param const float - Rotation on z
******************************************************************************/
void Object::SetRotation(const float RotationX_, const float RotationY_, const float RotationZ_)
{
	RotationX = RotationX_;

	RotationY = RotationY_;

	RotationZ = RotationZ_;
}

/*!****************************************************************************
 \brief Parent setter
 \param Object & - Reference to the objects parent
******************************************************************************/
void Object::SetParent(Object & Parent_)
{
	Parent = &Parent_;
}


