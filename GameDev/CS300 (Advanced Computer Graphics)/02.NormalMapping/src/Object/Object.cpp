/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Object.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #2
 \date    06/22/2020
 \brief   Object class functions definitions
******************************************************************************/
#include "Object.h"

Object::Object(ObjectType type) : RenderModeCount(0), ObjType(type), VAO(0), FaceNormalsVAO(0), AverageNormalsVAO(0), PositionBufferObject(0),
TextureCoordinatesBuffer(0), FaceNormalBuffer(0), AverageNormalBuffer(0),
WireFrameMode(false), TextureMapping(false), NormalRendering(false), AverageNormals(false), Precision(19), Rings(),
Position(glm::vec3(0.0f, 0.0f, 0.0f)), Scale(glm::vec3(1.0f, 1.0f, 1.0f)), Rotation(glm::vec3(0.0f, 0.0f, 0.0f))
{
	switch (ObjType)
	{
	case Plane:
		ComputePlaneVertices();
		break;
	case Cube:
		ComputeCubeVertices();
		break;
	case Cone:
		ComputeConeVertices(19, -0.001f);
		break;
	case Cylinder:
		ComputeCylinderVertices(19, -0.001f);
		break;
	case Sphere:
		ComputeSphereVertices(19, 7, -0.001f);
		break;
	}
}

void Object::ComputePlaneVertices()
{
	//Clear the vertices
	VertexPositions.clear();

	//Clear the uv
	VertexTextureCoordinates.clear();

	//Top right
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, 0.0f, 1.0f));

	// Bottom left 
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f));

	//Bottom right
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, 0.0f, 1.0f));

	//Top right
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, 0.0f, 1.0f));

	//Top left
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f));

	 // Bottom left 
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f));
		
	//Compute uv
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));

	//Compute the normals
	ComputeFaceNormals();
}

void Object::ComputeCubeVertices()
{
	//Clear the vertices
	VertexPositions.clear();

	//Clear the uv
	VertexTextureCoordinates.clear();
	
	//Back face
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	
	//Right face
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));

	//Front face
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
							
	//Left face
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));

	//Up face
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));		

	//Down face
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
	VertexPositions.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
	
	//Compute uv
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
											   
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
											   
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
											   
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
											   
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
											   
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	VertexTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));

	//Compute the normals
	ComputeFaceNormals();
}

void Object::ComputeConeVertices(const int Precision, const float epsilon)
{
	//Clear the vertices
	VertexPositions.clear();

	//Clear the uv
	VertexTextureCoordinates.clear();

	//Variables to store the current and next vertex
	glm::vec4 Current, Next;

	//Variable to store the middle vertices
	glm::vec4 BaseMiddle(0.0f, -0.5f, 0.0f , 1.0f);
	glm::vec4 BodyMiddle(0.0f, 0.5f, 0.0f, 1.0f);

	//Store the value of a entire round
	float angle = 2.0f * pi;

	//Goes from 0 to 2 pi 
	for (float i = 0.0f, j = 0.0f; i < angle + epsilon; i += (angle / Precision), j += 1.0f / Precision)
	{
		//Compute the current vertex
		Current.x = 0.5f * cosf(i);
		Current.y = -0.5f;
		Current.z = 0.5f * sinf(i);
		Current.w = 1.0f;

		//Compute the next vertex
		Next.x = 0.5f * cosf(i + angle / Precision);
		Next.y = -0.5f;
		Next.z = 0.5f * sinf(i + angle / Precision);
		Next.w = 1.0f;
		//Base

		//Current vertex position
		VertexPositions.push_back(Current);

		//Current vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f / Precision));

		//Next vertex position
		VertexPositions.push_back(Next);

		//Next vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j + 1.0f / Precision, 1.0f / Precision));

		//Base middle point position
		VertexPositions.push_back(BaseMiddle);

		//Base middle point uv
		VertexTextureCoordinates.push_back(glm::vec2(1.0f / Precision / 6.0f + j, 1.0f / Precision));

		//Body	

		//Current vertex position
		VertexPositions.push_back(Current);

		//Current vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f / Precision));

		//Middle top vertex position
		VertexPositions.push_back(BodyMiddle);

		//Middle top vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f));

		//Next vertex position
		VertexPositions.push_back(Next);

		//Next vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j + 1.0f / Precision, 1.0f / Precision));
	}

	//Compute the normals
	ComputeFaceNormals();
}

void Object::ComputeCylinderVertices(const int Precision, const float epsilon)
{
	//Clear the vertices
	VertexPositions.clear();

	//Clear the uv
	VertexTextureCoordinates.clear();

	//Variables to store the current and next vertex
	glm::vec4 Current, Next;

	//Variable to store the middle vertices
	glm::vec4 BaseMiddle(0.0f, -0.5f, 0.0f, 1.0f);
	glm::vec4 BodyMiddle(0.0f, 0.5f, 0.0f, 1.0f);

	//Store the value of a entire round
	float angle = 2.0f * pi;

	//Goes from 0 to 2 pi 
	for (float i = 0.0f, j = 0.0f; i < angle + epsilon; i += (angle / Precision), j += 1.0f / Precision)
	{
		//Compute the current vertex
		Current.x = 0.5f * cosf(i);
		Current.y = -0.5f;
		Current.z = 0.5f * sinf(i);
		Current.w = 1.0f;

		//Compute the next vertex
		Next.x = 0.5f * cosf(i + angle / Precision);
		Next.y = -0.5f;
		Next.z = 0.5f * sinf(i + angle / Precision);
		Next.w = 1.0f;

		//Base

		//Current vertex position
		VertexPositions.push_back(Current);

		//Current vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f / Precision));

		//Next vertex position
		VertexPositions.push_back(Next);

		//Next vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j + 1.0f / Precision, 1.0f / Precision));

		//Base middle point position
		VertexPositions.push_back(BaseMiddle);

		//Base middle point uv
		VertexTextureCoordinates.push_back(glm::vec2((1.0f / Precision / 6.0f) + j, 1.0f / Precision));

		//Up Base

		Current.y = 0.5f;
		Next.y = 0.5f;

		//Up base middle point position
		VertexPositions.push_back(BodyMiddle);

		//Up base middle point uv
		VertexTextureCoordinates.push_back(glm::vec2((1.0f / Precision / 6.0f) + j, 1.0f - 1.0f / Precision));

		//Up base next point position
		VertexPositions.push_back(Next);

		//Up base next point uv
		VertexTextureCoordinates.push_back(glm::vec2(j + (1.0f / Precision), 1.0f - (1.0f / Precision)));

		//Up base current point position
		VertexPositions.push_back(Current);

		//Up base current point uv
		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f - (1.0f / Precision)));

		//Body	

		Current.y = -0.5f;

		//First triangle
		VertexPositions.push_back(Current);

		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f / Precision));

		Current.y = 0.5f;

		VertexPositions.push_back(Current);

		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f));

		Next.y = -0.5f;

		VertexPositions.push_back(Next);

		VertexTextureCoordinates.push_back(glm::vec2(j + (1.0f / Precision), 1.0f / Precision));


		//Second triangle
		
		Current.y = 0.5f;

		VertexPositions.push_back(Current);

		VertexTextureCoordinates.push_back(glm::vec2(j, 1.0f));

		Next.y = 0.5f;

		VertexPositions.push_back(Next);

		VertexTextureCoordinates.push_back(glm::vec2(j + (1.0f / Precision), 1.0f));

		Next.y = -0.5f;

		VertexPositions.push_back(Next);

		VertexTextureCoordinates.push_back(glm::vec2(j + (1.0f / Precision), 1.0f / Precision));
	}

	//Compute the normals
	ComputeFaceNormals();
}

void Object::ComputeSphereVertices(const int Precision, const int Rings, const float epsilon)
{
	//Clear the vertices
	VertexPositions.clear();

	//Clear the uv
	VertexTextureCoordinates.clear();

	//Steps for the loops
	float angle = (2 * pi) / Precision;
	float angle2 = pi / Rings;
	
	//Vertices for sphere
	glm::vec4 v1, v2, v3, v4;

	//Goes throug the sphere except the top and bottom parts
	for (float i = angle2; i < pi - angle2 + epsilon; i += angle2)
	{
		for (float j = 0.0f ; j < 2.0f * pi + epsilon; j += angle)
		{
			//Compute the first vertice
			v1.x = 0.5f * sin(i) * cos(j + angle);
			v1.y = 0.5f * sin(i) * sin(j + angle);
			v1.z = 0.5f * cos(i);
			v1.w = 1.0f;

			//Compute the second vertice
			v2.x = 0.5f * sin(i + angle2) * cos(j);
			v2.y = 0.5f * sin(i + angle2) * sin(j);
			v2.z = 0.5f * cos(i + angle2);
			v2.w = 1.0f;

			//Compute the third vertice
			v3.x = 0.5f * sin(i) * cos(j);
			v3.y = 0.5f * sin(i) * sin(j);
			v3.z = 0.5f * cos(i);
			v3.w = 1.0f;

			//Compute the fourth vertice
			v4.x = 0.5f * sin(i + angle2) * cos(j + angle);
			v4.y = 0.5f * sin(i + angle2) * sin(j + angle);
			v4.z = 0.5f * cos(i + angle2);
			v4.w = 1.0f;

			//Adds the second vertices positions
			VertexPositions.push_back(v2);

			//Adds the second vertices uv
			VertexTextureCoordinates.push_back(glm::vec2((i + angle2) / (2.0f * pi), j / (2.0f * pi)));

			//Adds the first vertices positions
			VertexPositions.push_back(v1);

			//Adds the first vertices uv
			VertexTextureCoordinates.push_back(glm::vec2(i / (2.0f * pi), (j + angle) / (2.0f * pi)));

			//Adds the third vertices positions
			VertexPositions.push_back(v3);

			//Adds the second vertices uv
			VertexTextureCoordinates.push_back(glm::vec2(i / (2.0f * pi), j / (2.0f * pi)));


			//Adds the third vertices positions
			VertexPositions.push_back(v2);

			//Adds the third vertices uv
			VertexTextureCoordinates.push_back(glm::vec2((i + angle2) / (2.0f * pi), j / (2.0f * pi)));
	

			//Adds the third vertices positions
			VertexPositions.push_back(v4);

			//Adds the second vertices uv
			VertexTextureCoordinates.push_back(glm::vec2((i + angle2) / (2.0f * pi), (j + angle) / (2.0f * pi)));


			//Adds the fourth vertices positions
			VertexPositions.push_back(v1);

			//Adds the fourth vertices uv
			VertexTextureCoordinates.push_back(glm::vec2(i / (2.0f * pi), (j + angle) / (2.0f * pi)));	


		}
	}

	//Goes through the top and bottom part of the sphere
	for (float i = 0.0f, j = pi - angle / Precision, k = pi/3.5f - angle/2.0f; i < 2.0f * pi + epsilon; i += angle, j-= angle, k-=angle)
	{
		//Bottom base
		//Computes the first vertex
		v1.x = 0.5f * sin(angle2) * cos(i);
		v1.y = 0.5f * sin(angle2) * sin(i);
		v1.z = 0.5f * cos(angle2);
		v1.w = 1.0f;

		//Computes the second vertex
		v2.x = 0.5f * sin(angle2) * cos(i + angle);
		v2.y = 0.5f * sin(angle2) * sin(i + angle);
		v2.z = 0.5f * cos(angle2);
		v2.w = 1.0f;

		//Computes the middle vertex
		v3.x = 0.0f;
		v3.y = 0.0f;
		v3.z = 0.5f;
		v3.w = 1.0f;
		
		//Adds the third vertex position
		VertexPositions.push_back(v3);

		//Adds the third vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(k / (2.0f * pi), ((i + angle) / (2.0f * pi)) / 6.0f));

		//Adds the first vertex position
		VertexPositions.push_back(v1);

		//Adds the first vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(k / (2.0f * pi), ((i + angle) / (2.0f * pi)) / 6.0f));
	

		//Adds the second vertex position
		VertexPositions.push_back(v2);

		//Adds the second vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(k / (2.0f * pi), ((i + angle) / (2.0f * pi)) / 6.0f));
	
		//Top base

		//Compute the first vertex
		v1.x = 0.5f * sin(pi - angle2) * cos(i);
		v1.y = 0.5f * sin(pi - angle2) * sin(i);
		v1.z = 0.5f * cos(pi - angle2);
		v1.w = 1.0f;
	
		//Compute the second vertex
		v2.x = 0.5f * sin(pi - angle2) * cos(i + angle);
		v2.y = 0.5f * sin(pi - angle2) * sin(i + angle);
		v2.z = 0.5f * cos(pi - angle2);
		v2.w = 1.0f;
	
		//Compute the middle vertex
		v3.x = 0.0f;
		v3.y = 0.0f;
		v3.z = -0.5f;
		v3.w = 1.0f;
		//Adds the third vertex position
		VertexPositions.push_back(v3);

		//Adds the third vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j / (2.0f * pi), ((i + angle) / (2.0f * pi)) / 6.0f));	

		//Adds the second vertex position
		VertexPositions.push_back(v2);

		//Adds the second vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j / (2.0f * pi), ((i + angle) / (2 * pi)) / 6.0f));

		//Adds the first vertex position
		VertexPositions.push_back(v1);

		//Adds the first vertex uv
		VertexTextureCoordinates.push_back(glm::vec2(j / (2.0f * pi), ((i + angle) / (2.0f * pi)) / 6.0f));

	}

	//Compute the normals
	ComputeFaceNormals();
}

void Object::ComputeFaceNormals()
{
	//Vector to store the normals
	glm::vec3 save;

	//Clears the normals vector
	FaceNormals.clear();

	//Clear the normals
	Normals.clear();

	//Goes through all the vertices
	for (unsigned i = 0; i < VertexPositions.size(); i+=3)
	{
		//Compute the normals between 3 point
		save = triangleNormal(glm::vec3(VertexPositions[i]),
								  glm::vec3(VertexPositions[i + 1]),
				                  glm::vec3(VertexPositions[i + 2]));


		//First vertice
		FaceNormals.push_back(glm::vec3(VertexPositions[i]));
		
		//First VertexPositions +  the normal
		FaceNormals.push_back(0.2f * save + glm::vec3(VertexPositions[i]));

		Normals.push_back(save);

		//Second vertice
		FaceNormals.push_back(glm::vec3(VertexPositions[i + 1]));
		
		//Second vertice + the normal 
		FaceNormals.push_back(0.2f * save + glm::vec3(VertexPositions[i + 1]));
		
		Normals.push_back(save);

		//Third vertice
		FaceNormals.push_back(glm::vec3(VertexPositions[i + 2]));
		
		//Third vertice + the normal
		FaceNormals.push_back(0.2f * save + glm::vec3(VertexPositions[i + 2]));

		Normals.push_back(save);
	}

	//Compute the average normals
	ComputeAverageNormals();

	//Compute tangents and bitangents
	ComputeTangentBasis();
}

void Object::ComputeAverageNormals()
{
	//Vector to store the normals
	std::vector<glm::vec3> save = FaceNormals;

	//Clear the vector of average normals
	AverageNormals.clear();

	AverageNormalsVectors.clear();

	//Goes thorugh all the normals
	for (unsigned i = 0; i < save.size(); i+=2)
	{
		//Create the a vector to store the indices of the repited vertices
		std::vector<unsigned> Remove;

		//Goes through  the vertices with normals
		for (unsigned j = 0; j < save.size(); j += 2)
		{
			//Condition where two equal vertices are found
			if (save[i]==save[j])
			{
				//Add the indice to the vector
				Remove.push_back(j);
			}
		}

		//Create a vector to store the wanted normals
		std::vector<glm::vec3> Add;

		//Go through the indices 
		for (unsigned k = 0; k < Remove.size(); k++)
		{
			//Add the normal
			Add.push_back(save[Remove[k] + 1] - save[Remove[k]]);
		}

		//Create a vec3 to store the average normals
		glm::vec3 averageNormal(0.0f, 0.0f, 0.0f);

		//Go throught the saved normals
		for (unsigned b = 0; b < Add.size(); b++)
		{
			//Adds all the normals
			averageNormal += Add[b];
		}

		//Push the vertices with normals
		AverageNormals.push_back(save[Remove[0]]);

		//Push the average normals
		AverageNormals.push_back(glm::vec3(save[Remove[0]].x + averageNormal.x / Add.size(),
										   save[Remove[0]].y + averageNormal.y / Add.size(),
										   save[Remove[0]].z + averageNormal.z / Add.size()));

		AverageNormalsVectors.push_back(glm::vec3(save[Remove[0]].x + averageNormal.x / Add.size(),
												  save[Remove[0]].y + averageNormal.y / Add.size(),
												  save[Remove[0]].z + averageNormal.z / Add.size()));

		//Clear the remove vector
		Remove.clear();
	}
}

void Object::ComputeTangentBasis()
{
	// Clear and initialize tangent and bitangent containers
	tangents.clear();
	bitangents.clear();
	tangents.resize(VertexPositions.size(), glm::vec3(0.0f));
	bitangents.resize(VertexPositions.size(), glm::vec3(0.0f));

	std::vector<glm::vec3> save;
	
	//Condition for the avergae normals
	if (AverageNormalsBool && ObjType != Plane)
		save = AverageNormalsVectors;

	else
		save = Normals;

	// Loop through the triangles (using the index buffer)
	for (unsigned i = 0; i < VertexPositions.size(); i += 3)
	{
		glm::vec3 Vertex1 = VertexPositions[i];
		glm::vec3 Vertex2 = VertexPositions[i + 1];
		glm::vec3 Vertex3 = VertexPositions[i + 2];

		glm::vec3 V1 = Vertex2 - Vertex1;
		glm::vec3 V2 = Vertex3 - Vertex1;

		glm::vec2 UV1 = VertexTextureCoordinates[i];
		glm::vec2 UV2 = VertexTextureCoordinates[i + 1];
		glm::vec2 UV3 = VertexTextureCoordinates[i + 2];

		glm::vec2 S1T1 = UV2 - UV1;
		glm::vec2 S2T2 = UV3 - UV1;

		float r = S1T1.y * S2T2.x - S2T2.y * S1T1.x;

		if (r == 0.0f)
			r = 0.0f;

		else
			r = 1.0f / r;

		glm::vec3 T = (S1T1.y * V2 - S2T2.y * V1) * r;

		glm::vec3 B = (S2T2.x * V1 - S1T1.x * V2) * r;

		// Accumulate tangent/bitangent for the 3 vertices of the triangle (to average after)
		tangents[i] += T;
		tangents[i + 1] += T;
		tangents[i + 2] += T;

		bitangents[i] += B;
		bitangents[i + 1] += B;
		bitangents[i + 2] += B;
	}

	//Condition for the average normals
	if (AverageNormalsBool)
	{
		//Saves the tangents and bitangents
		std::vector<glm::vec3> TangentsSave = tangents;
		std::vector<glm::vec3> BitangentsSave = bitangents;

		//Clear and resize the vector
		tangents.clear();
		bitangents.clear();
		tangents.resize(VertexPositions.size(), glm::vec3(0.0f));
		bitangents.resize(VertexPositions.size(), glm::vec3(0.0f));

		//Go through the vertices
		for (unsigned i = 0; i < VertexPositions.size(); i++)
		{
			//Go through the vertices
			for (unsigned j = 0; j < VertexPositions.size(); j++)
			{
				//Check for equal vertices
				if (VertexPositions[i] == VertexPositions[j])
				{
					//Adds the tangents and bitangents
					tangents[i] += TangentsSave[j];
					bitangents[i] += BitangentsSave[j];
				}
			}

			//Checks if the tangent is 0, if not normalize
			if (tangents[i] == glm::vec3(0.0f))
				tangents[i] = glm::vec3(1.0f, 0.0f, 0.0f);

			else
				tangents[i] = normalize(tangents[i]);

			//Checks if the bitangent is 0, if not normalize
			if (bitangents[i] == glm::vec3(0.0f))
				bitangents[i] = glm::vec3(0.0f, 0.0f, 0.0f);

			else
				bitangents[i] = normalize(bitangents[i]);
		}
	}

	// Loop through every vertex
	for (unsigned i = 0; i < VertexPositions.size(); i++)
	{
		// Gram-Schmidt orthogonalization of tangent respect to normal and normalize tangent
		// Compute the new perpendicular bitangent maintaining the original handeness of the previously 
		// computed one (T,B,N need to be normalized and orthogonal at this point)

		if (glm::length(save[i]) != 0.0f)
			glm::normalize(save[i]);

		if (tangents[i] == glm::vec3(0.0f))
			tangents[i] = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			tangents[i] = glm::normalize(tangents[i] - save[i] * glm::dot(save[i], tangents[i]));

		if (glm::length(tangents[i]) != 0.0f)
			glm::normalize(tangents[i]);

		if (glm::dot(glm::cross(save[i], tangents[i]), bitangents[i]) < 0.0f)
			bitangents[i] = glm::cross(save[i], tangents[i]) * -1.0f;

		else
			bitangents[i] = glm::cross(save[i], tangents[i]);

		if (glm::length(bitangents[i]) != 0.0f)
			glm::normalize(bitangents[i]);
	}

	//Clears the tangents and bitangetns to draw
	TangentsDraw.clear();
	BitangentsDraw.clear();

	//Resize the vectors
	TangentsDraw.resize(tangents.size() * 2);
	BitangentsDraw.resize(tangents.size() * 2);

	//Compute the tangents and bitangents for drawing
	for (unsigned i = 0; i < tangents.size(); i++)
	{
		//Adds the point and the point plus the vector of the tangents
		TangentsDraw.push_back(VertexPositions[i]);
		TangentsDraw.push_back(glm::vec3(VertexPositions[i]) + tangents[i] * 0.2f);

		//Adds the point and the point plus the vector of the bitangents
		BitangentsDraw.push_back(VertexPositions[i]);
		BitangentsDraw.push_back(glm::vec3(VertexPositions[i]) + bitangents[i] * 0.2f);
	}

	//Compute the averege tangents and bitangents for drawing
	if (AverageNormalsBool)
	{
		//Computes the averge tangents and bitangents to draw
		TangentsDraw = ComputeAverageNormalsToDraw(TangentsDraw);
		BitangentsDraw = ComputeAverageNormalsToDraw(BitangentsDraw);
	}

}

std::vector<glm::vec3> Object::ComputeAverageNormalsToDraw(const std::vector<glm::vec3>& rhs)
{
	//Vector to store the resulting vector
	std::vector<glm::vec3> Solution;

	//Vector to save the wanted vector
	std::vector<glm::vec3> Save;

	//Go through the vertices
	for (unsigned i = 0; i < VertexPositions.size(); i++)
	{
		//Saves the current point
		glm::vec3 point = VertexPositions[i];

		//Clears the save vector
		Save.clear();

		//Goes through the given vector
		for (unsigned j = 0; j < rhs.size(); j+=2)
		{
			//Checks for equal points
			if (point == rhs[j])
			{
				//Saves the vector
				Save.push_back(rhs[j + 1] - point);			
			} 
		}

		//Create a vec3 for the average
		glm::vec3 Average = glm::vec3();

		//Goes through the saved vertices
		for (unsigned j = 0; j < Save.size(); j++)
		{
			//Adds the vectors
			Average += Save[j];
		}

		//Computes the average
		Average /= Save.size();

		//Normalizes the average
		normalize(Average);
		
		//Adds the point
		Solution.push_back(point);

		//Adds the point and the average
		Solution.push_back(point + Average);
	}

	//Return the vector
	return Solution;
}

//Getters

ObjectType & Object::GetObjectType()
{
	return ObjType;
}

GLuint & Object::GetVAO()
{
	return VAO;
}

GLuint & Object::GetFaceNormalsVAO()
{
	return FaceNormalsVAO;
}

GLuint & Object::GetAverageNormalsVAO()
{
	return AverageNormalsVAO;
}

GLuint & Object::GetPositionBufferObject()
{
	return PositionBufferObject;
}

GLuint & Object::GetTextureCoordinatesBuffer()
{
	return TextureCoordinatesBuffer;
}

GLuint & Object::GetNormalsBuffer()
{
	return FaceNormalBuffer;
}

GLuint & Object::GetAverageNormalsBuffer()
{
	return AverageNormalBuffer;
}

std::vector<glm::vec4> Object::GetVertexPositions()
{
	return VertexPositions;
}

std::vector<glm::vec2> Object::GetVertexTextureCoordinates()
{
	return VertexTextureCoordinates;
}

std::vector<glm::vec3> Object::GetFaceNormals()
{
	return FaceNormals;
}

std::vector<glm::vec3> Object::GetAverageNormals()
{
	return AverageNormals;
}

bool Object::GetWireFrameMode()
{
	return WireFrameMode;
}

bool Object::GetTextureMapping()
{
	return TextureMapping;
}

bool Object::GetNormalRendering()
{
	return NormalRendering;
}

bool Object::GetAverageNormalsBool()
{
	return AverageNormalsBool;
}

int Object::GetPrecision()
{
	return Precision;
}

int Object::GetRings()
{
	return Rings;
}

glm::vec3 Object::GetPosition()
{
	return Position;
}

glm::vec3 Object::GetScale()
{
	return Scale;
}

glm::vec3 Object::GetRotation()
{
	return Rotation;
}

//Setters

void Object::SetObjectType(ObjectType type)
{
	ObjType = type;
}

void Object::SetWireFrameMode(bool value)
{
	WireFrameMode = value;
}

void Object::SetTextureMapping(bool value)
{
	TextureMapping = value;
}

void Object::SetNormalRendering(bool value)
{
	NormalRendering = value;
}

void Object::SetAverageNormals(bool value)
{
	AverageNormalsBool = value;
}

void Object::SetPrecision(int precision_)
{
	Precision = precision_;
}

void Object::SetRings(int rings_)
{
	Rings = rings_;
}

void Object::UpdatePosition(const glm::vec3 & pos)
{
	Position += pos;
}

void Object::SetPosition(glm::vec3 pos)
{
	Position = pos;
}

void Object::SetScale(glm::vec3 scale)
{
	Scale = scale;
}

void Object::SetRotation(glm::vec3 rotation)
{
	Rotation = rotation;
}
