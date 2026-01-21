/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Object.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #4
 \date    02/27/2020
 \brief   Object class functions definitions
******************************************************************************/

#include "Object.h"
#include <algorithm>

/*!****************************************************************************
 \brief Object default constructor
******************************************************************************/
Object::Object(): Translation(Point4()), Scale(Point4()), RotationX(0), 
				  RotationY(0), RotationZ(0), Vertices(0), Parent(nullptr),
				  Up(Vector4(0,1,0,0)), Forward(Vector4(0, 0, 1, 0)),
				  Right(Forward.Cross(Up)){}

/*!****************************************************************************
 \brief Renders the object
 \param sf::Image & - Reference to the image created in main
 \param bool - Determines if the Wireframe mode is on or not
 \param CameraMode - Determines the camera mode
 \param camera_ - Reference to the current camera
******************************************************************************/
void Object::Render(sf::Image & image, bool Wireframe_, CameraMode cameramode, Camera & camera_, std::vector<float> & ZBuffer_)
{
	//Normalize foward vector
	Forward.Normalize();

	//Normalize Up vector
	Up.Normalize();

	//Normalize Right vector
	Right.Normalize();

	//Computes the model to world
	ModelToWorld();

	//Computes the model to world
	OrthogonalMethodInverse(camera_);

	//Compute the frustum planes
	FrustumPlane();
	//Saves the vertices
	SaveVertices = Vertices;

	//Goes through all the vertices
	for (unsigned i = 0; i < SaveVertices.size(); i += 3)
	{

		//Transforms to world coordinates the 3 vertices
		SaveVertices[i].mPosition = ModelToWorldMatrix * SaveVertices[i].mPosition;
		SaveVertices[i+1].mPosition = ModelToWorldMatrix * SaveVertices[i+1].mPosition;
		SaveVertices[i+2].mPosition = ModelToWorldMatrix * SaveVertices[i+2].mPosition;


		//Check for culling and backface removal
		if (Culling(SaveVertices[i], SaveVertices[i + 1], SaveVertices[i + 2])||
		BackFaceRemove(SaveVertices[i], SaveVertices[i + 1], SaveVertices[i + 2], camera_))
		{
			continue;
		}

		//Vector for the clipped points
		std::vector<Rasterizer::Vertex> ClipledPoint;
		
		//Calculates the clipped points
		ClipledPoint = Clipping(SaveVertices[i], SaveVertices[i + 1], SaveVertices[i + 2]);

		//If the are not any points in the clipled vector go to the next vertices
		if (ClipledPoint.size() == 0)
		{
			continue;
		}

		//Goes through the cliped points
		for (unsigned j = 0; j < ClipledPoint.size(); j++)
		{
			//Computes the camera to projection window matrix for the vertices
			ClipledPoint[j].mPosition = CameraToProjectionWindowMatrix * WorldToCameraMatrix * ClipledPoint[j].mPosition;

			//Computes the perspective division
			ClipledPoint[j].mPosition.x = ClipledPoint[j].mPosition.x / ClipledPoint[j].mPosition.w;
			ClipledPoint[j].mPosition.y = ClipledPoint[j].mPosition.y / ClipledPoint[j].mPosition.w;
			ClipledPoint[j].mPosition.z = ClipledPoint[j].mPosition.z / ClipledPoint[j].mPosition.w;
			ClipledPoint[j].mPosition.w = ClipledPoint[j].mPosition.w / ClipledPoint[j].mPosition.w;

			//Multiplies the Window to viewport matrix with the vertices
			ClipledPoint[j].mPosition = ProjectionWindowToViewportMatrix * ClipledPoint[j].mPosition;
		}

		//Checks it the Wireframe is false
		if (!Wireframe_)
		{
			//If the are 3 points just render 1 triangle
			if (ClipledPoint.size() == 3)
			{
				//Drawsthe triangles with three points
				DrawTriangleSolid(
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b),
					Point2D(ClipledPoint[1].mPosition.x, ClipledPoint[1].mPosition.y, ClipledPoint[1].mPosition.z,
						ClipledPoint[1].mColor.r, ClipledPoint[1].mColor.g, ClipledPoint[1].mColor.b),
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b), image, ZBuffer_);
			}

			//If the are 4 points just render 2 triangles
			else if (ClipledPoint.size() == 4)
			{
				//Drawsthe triangles with three points
				DrawTriangleSolid(
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b),
					Point2D(ClipledPoint[1].mPosition.x, ClipledPoint[1].mPosition.y, ClipledPoint[1].mPosition.z,
						ClipledPoint[1].mColor.r, ClipledPoint[1].mColor.g, ClipledPoint[1].mColor.b),
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b), image, ZBuffer_);

				//Drawsthe triangles with three points
				DrawTriangleSolid(
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b),
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b),
					Point2D(ClipledPoint[3].mPosition.x, ClipledPoint[3].mPosition.y, ClipledPoint[3].mPosition.z,
						ClipledPoint[3].mColor.r, ClipledPoint[3].mColor.g, ClipledPoint[3].mColor.b), image, ZBuffer_);
			}
		}

		//Wireframe mode on
		else
		{
			//If the are 3 points just render 1 triangle
			if (ClipledPoint.size() == 3)
			{
				//Draws a line between the first and the second point for the first side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b),
					Point2D(ClipledPoint[1].mPosition.x, ClipledPoint[1].mPosition.y, ClipledPoint[1].mPosition.z,
						ClipledPoint[1].mColor.r, ClipledPoint[1].mColor.g, ClipledPoint[1].mColor.b), image);

				//Draws a line between the second and the third point for the second side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[1].mPosition.x, ClipledPoint[1].mPosition.y, ClipledPoint[1].mPosition.z,
						ClipledPoint[1].mColor.r, ClipledPoint[1].mColor.g, ClipledPoint[1].mColor.b),
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b), image);

				//Draws a line between the third and the first point for the third side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b),
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b), image);
			}

			//If the are 4 points just render 2 triangles
			if (ClipledPoint.size() == 4)
			{
				//Draws a line between the first and the second point for the first side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b),
					Point2D(ClipledPoint[1].mPosition.x, ClipledPoint[1].mPosition.y, ClipledPoint[1].mPosition.z,
						ClipledPoint[1].mColor.r, ClipledPoint[1].mColor.g, ClipledPoint[1].mColor.b), image);

				//Draws a line between the second and the third point for the second side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[1].mPosition.x, ClipledPoint[1].mPosition.y, ClipledPoint[1].mPosition.z,
						ClipledPoint[1].mColor.r, ClipledPoint[1].mColor.g, ClipledPoint[1].mColor.b),
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b), image);

				//Draws a line between the third and the first point for the third side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b),
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b), image);

				//Draws a line between the first and the second point for the first side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b),
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b), image);

				//Draws a line between the second and the third point for the second side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[2].mPosition.x, ClipledPoint[2].mPosition.y, ClipledPoint[2].mPosition.z,
						ClipledPoint[2].mColor.r, ClipledPoint[2].mColor.g, ClipledPoint[2].mColor.b),
					Point2D(ClipledPoint[3].mPosition.x, ClipledPoint[3].mPosition.y, ClipledPoint[3].mPosition.z,
						ClipledPoint[3].mColor.r, ClipledPoint[3].mColor.g, ClipledPoint[3].mColor.b), image);

				//Draws a line between the third and the first point for the third side of the triangle
				DrawMidpointLine(
					Point2D(ClipledPoint[3].mPosition.x, ClipledPoint[3].mPosition.y, ClipledPoint[3].mPosition.z,
						ClipledPoint[3].mColor.r, ClipledPoint[3].mColor.g, ClipledPoint[3].mColor.b),
					Point2D(ClipledPoint[0].mPosition.x, ClipledPoint[0].mPosition.y, ClipledPoint[0].mPosition.z,
						ClipledPoint[0].mColor.r, ClipledPoint[0].mColor.g, ClipledPoint[0].mColor.b), image);
			}
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

	//Computes the matrix for all the rotation
	Matrix4 RotationMatrix = Matrix4(-Right.x, Up.x, Forward.x, 0,
									 -Right.y, Up.y, Forward.y, 0,
									 -Right.z, Up.z, Forward.z, 0,
									 0, 0, 0, 1);

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
		//Computes the model to world of the parent matrix
		ParentModelToWorldMatrix = Matrix4(-Parent->Right.x, Parent->Up.x, Parent->Forward.x, Parent->Translation.x,
										   -Parent->Right.y, Parent->Up.y, Parent->Forward.y, Parent->Translation.y,
										   -Parent->Right.z, Parent->Up.z, Parent->Forward.z, Parent->Translation.z,
										   0, 0, 0, 1)
			* ParentModelToWorldMatrix;

		//Calls the parents ParentModelToWorld fuction in case the parent also has parents
		Parent->ParentModelToWorld(ParentModelToWorldMatrix);
	}	
}

/*!****************************************************************************
 \brief Computes the world to camera
 \param camera_ - Reference to the current camera
******************************************************************************/
void Object::OrthogonalMethodInverse(Camera & camera_)
{
	//Sets the value of A with the COP
	Vector4 A = Vector4(camera_.GetCOP().x, camera_.GetCOP().y, camera_.GetCOP().z, 0);

	//Sets the value of u with the view vector of the camera
	Vector4 u = camera_.GetViewVector();

	//Noramalize u
	u.Normalize();

	//Sets the value of v with the up vector of the camera
	Vector4 v = camera_.GetUpVector();

	//Noramalize v
	v.Normalize();

	//Sets the value of w with the up vector of the camera
	Vector4 w = camera_.GetRightVector();

	//Noramalize w
	w.Normalize();

	//Computes the world to camera matrix
	WorldToCameraMatrix = Matrix4(w.x, w.y, w.z, -(w.x * A.x + w.y* A.y + w.z * A.z),
								  v.x, v.y, v.z, -(v.x * A.x + v.y* A.y + v.z * A.z),
								 -u.x, -u.y, -u.z, (u.x * A.x + u.y* A.y + u.z * A.z),
								  0, 0, 0, 1);
}


/*!****************************************************************************
 \brief Computes the axis angle method
 \param Vector4 & - Rotation axis
 \param float - Angle to rotate
******************************************************************************/
void Object::AxisAngleMethod(Vector4 & RotationAxis_, float angle_)
{
	//Compute a identity matrix
	Matrix4 Identity;	Identity.Identity();
	
	//Compute the tensor product
	Matrix4 TensorProduct = Matrix4(RotationAxis_.x * RotationAxis_.x,
									RotationAxis_.x * RotationAxis_.y, 
									RotationAxis_.x * RotationAxis_.z, 0,
									RotationAxis_.y * RotationAxis_.x,
									RotationAxis_.y * RotationAxis_.y,
									RotationAxis_.y * RotationAxis_.z, 0,
									RotationAxis_.z * RotationAxis_.x,
									RotationAxis_.z * RotationAxis_.y,
									RotationAxis_.z * RotationAxis_.z, 0,
									0, 0, 0, 1);

	//Computes the cross product
	Matrix4 CrossProduct = Matrix4(0, -RotationAxis_.z, RotationAxis_.y, 0,
								   RotationAxis_.z, 0, -RotationAxis_.x, 0,
								   -RotationAxis_.y, RotationAxis_.x, 0, 0,
								   0, 0, 0, 1);

	//Compute the rotation matrix
	AxisAngleMethodMatrix = Identity * cos(angle_) + 
	TensorProduct * (1 - cos(angle_)) + CrossProduct * sin(angle_);

	//Sets the last row correctly
	AxisAngleMethodMatrix.m[3][0] = 0;
	AxisAngleMethodMatrix.m[3][1] = 0;
	AxisAngleMethodMatrix.m[3][2] = 0;
	AxisAngleMethodMatrix.m[3][3] = 1;

}

/*!****************************************************************************
 \brief Computes the 6 frustum planes
******************************************************************************/
void Object::FrustumPlane()
{
	//Computes the perspective matrix
	Matrix4 m =  CameraToProjectionWindowMatrix * WorldToCameraMatrix;

	//Save the 4 rows
	Vector4 s0 = Vector4(m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]);

	Vector4 s1 = Vector4(m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]);

	Vector4 s2 = Vector4(m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]);

	Vector4 s3 = Vector4(m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);

	//Computes the 6 frustum planes
	LeftPlane = -s0 - s3;
	RightPlane = s0 - s3;
	BottomPlane = -s1 - s3;
	TopPlane = s1 - s3;
	NearPlane = -s2 - s3;
	FarPlane = s2 - s3;
}
/*!****************************************************************************
 \brief Checks if a faces is on the back
 \param Rasterizer::Vertex - First point
 \param Rasterizer::Vertex - Second point
 \param Rasterizer::Vertex - Third point
 \return bool - Returns if the face needs to be rendered or not
******************************************************************************/
bool Object::BackFaceRemove(Rasterizer::Vertex p0, Rasterizer::Vertex p1, Rasterizer::Vertex p2, Camera & camera)
{
	//Computes the vectors of the triangle
	Vector4 v0 = p1.mPosition - p0.mPosition;
	Vector4 v1 = p2.mPosition - p0.mPosition;

	//Computes the face normal
	Vector4 n = v0.Cross(v1) / v0.Cross(v1).Length();

	//Computes the vertex eye vector
	Vector4 VertexEye = p0.mPosition - camera.GetCOP();

	//Checks if the vectors are in opposite direction
	if (n.Dot(VertexEye) < 0)
	{
		//We dont have to render the triangle
		return false;
	}

	//Same directions
	else
	{
		//Render the triangle
		return true;
	}
	
}

/*!****************************************************************************
 \brief Checks for culling
 \param Rasterizer::Vertex - First point
 \param Rasterizer::Vertex - Second point
 \param Rasterizer::Vertex - Third point
 \return bool - Returns if culling needs to be done or not
******************************************************************************/
bool Object::Culling(Rasterizer::Vertex p0, Rasterizer::Vertex p1, Rasterizer::Vertex p2)
{
	//Push the planes into a vector
	std::vector<Vector4> Planes;
	Planes.push_back(LeftPlane);
	Planes.push_back(RightPlane);
	Planes.push_back(BottomPlane);
	Planes.push_back(TopPlane);
	Planes.push_back(NearPlane);
	Planes.push_back(FarPlane);

	//Save the vertices has vectors
	Vector4 P0 = Vector4(p0.mPosition.x, p0.mPosition.y, p0.mPosition.z);
	Vector4 P1 = Vector4(p1.mPosition.x, p1.mPosition.y, p1.mPosition.z);
	Vector4 P2 = Vector4(p2.mPosition.x, p2.mPosition.y, p2.mPosition.z);

	//Go through all the planes
	for (unsigned i = 0; i < Planes.size(); i++)
	{
		//Checks if the point is infront of the near plane
		if (Planes[i].Dot(P0) + Planes[i].w > 0 && Planes[i].Dot(P1) + Planes[i].w > 0 && Planes[i].Dot(P2) + Planes[i].w > 0)
			return true;
	}

	//Return false if its not in front
	return false;
}

/*!****************************************************************************
 \brief Computes clipping
 \param Rasterizer::Vertex - First point
 \param Rasterizer::Vertex - Second point
 \param Rasterizer::Vertex - Third point
 \return std::vector<Point4> - Clipped points
******************************************************************************/
std::vector<Rasterizer::Vertex> Object::Clipping(Rasterizer::Vertex p0, Rasterizer::Vertex p1, Rasterizer::Vertex p2)
{
	//Saves the vertices
	std::vector<Rasterizer::Vertex> Segments;
	Segments.push_back(p0);
	Segments.push_back(p1);
	Segments.push_back(p1);
	Segments.push_back(p2);
	Segments.push_back(p2);
	Segments.push_back(p0);

	//Vector to store the vertices
	std::vector<Rasterizer::Vertex> Result;

	//Goes through the segments
	for (unsigned i = 0; i < Segments.size(); i+=2)
	{
		//Checks if the start and the end point are behind
		if (Behind(Segments[i]) && Behind(Segments[i+1]))
		{
			Result.push_back(Segments[i+1]);
		}

		//Checks if the start is behind and the end point in front
		else if (Behind(Segments[i]) && InFront(Segments[i + 1]))
		{
			Point4 p = IntersectionPoint(Segments[i], Segments[i + 1]);
			Rasterizer::Vertex V;
			V.mPosition = p;
			V.mColor = Segments[i].mColor;
			Result.push_back(V);
		}

		//Checks if the start is in front and the end point behind
		else if (InFront(Segments[i]) && Behind(Segments[i + 1]))
		{
			Point4 p = IntersectionPoint(Segments[i], Segments[i + 1]);
			Rasterizer::Vertex V;
			V.mPosition = p;
			V.mColor = Segments[i].mColor;
			Result.push_back(V);
			Result.push_back(Segments[i + 1]);
		}
	}

	return Result;
}

/*!****************************************************************************
 \brief Checks if the point is behind the nearplane
 \param Rasterizer::Vertex - Points to check if its behind the plane
 \return bool - Returns if the point is behind or not
******************************************************************************/
bool Object::Behind(Rasterizer::Vertex p)
{
	//Saves the point in a vector
	Vector4 v = Vector4(p.mPosition.x, p.mPosition.y, p.mPosition.z);

	//Check if the point is behind
	if(NearPlane.Dot(v) + NearPlane.w < 0)
		return true;

	return false;
}

/*!****************************************************************************
 \brief Checks if the point is in front the nearplane
 \param Rasterizer::Vertex - Points to check if its in front the plane
 \return bool - Returns if the point is in front or not
******************************************************************************/
bool Object::InFront(Rasterizer::Vertex p)
{
	//Saves the point in a vector
	Vector4 v = Vector4(p.mPosition.x, p.mPosition.y, p.mPosition.z);

	//Check if the point is in front
	if (NearPlane.Dot(v) + NearPlane.w > 0)
		return true;

	return false;
}

/*!****************************************************************************
 \brief Checks if the
 \param Rasterizer::Vertex - Points to check if its behind the plane
 \return std::vector<Point4> - Clipped points
******************************************************************************/
Point4 Object::IntersectionPoint(Rasterizer::Vertex p0, Rasterizer::Vertex p1)
{
	//Normalices the nearplane
	NearPlane.Normalize();

	//Computes the segment
	Vector4 p = p1.mPosition - p0.mPosition;

	//Computes the time of intersection
	float t = (-(NearPlane.x * p0.mPosition.x + NearPlane.y * p0.mPosition.y + NearPlane.z * p0.mPosition.z) - NearPlane.w)
				/ NearPlane.Dot(p);

	//Computes the intersection point
	return p0.mPosition + p * t;
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


