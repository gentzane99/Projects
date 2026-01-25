/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Object.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #1
 \date    07/10/2020
 \brief   Object class declaration
******************************************************************************/
#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/gtx/normal.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../GLSLProgram/GLSLProgram.h"

//Object types
enum ObjectType { Plane, Cube, Cone, Cylinder, Sphere };

//Variable for the pi value
const float pi = glm::pi<float>();

class Object
{
public:

	//Shape constructor
	Object(ObjectType);

	//Compute the vertices and uv for all the shapes
	void ComputePlaneVertices();
	void ComputeCubeVertices();
	void ComputeConeVertices(const int, const float);
	void ComputeCylinderVertices(const int, const float);
	void ComputeSphereVertices(const int, const int, const float);

	//Compute the face normals
	void ComputeFaceNormals();

	//Compute the average normals
	void ComputeAverageNormals();

	//Getter for the object type
	ObjectType & GetObjectType();

	//VAOs getters
	GLuint & GetVAO();
	GLuint & GetFaceNormalsVAO();
	GLuint & GetAverageNormalsVAO();

	//VBOs getters
	GLuint & GetPositionBufferObject();
	GLuint & GetTextureCoordinatesBuffer();
	GLuint & GetNormalsBuffer();
	GLuint & GetAverageNormalsBuffer();

	//Getters of the vertices, UVs and normals
	std::vector<glm::vec4> GetVertexPositions();
	std::vector<glm::vec2> GetVertexTextureCoordinates();
	std::vector<glm::vec3> GetFaceNormals();
	std::vector<glm::vec3> GetAverageNormals();

	//Getter for the wireframe mode
	bool GetWireFrameMode();

	//Getter for the uv mode
	bool GetTextureMapping();

	//Getter for the face normals rendering
	bool GetNormalRendering();

	//Getter for the average normals rendering
	bool GetAverageNormalsBool();

	//Getters for the transformations
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();

	//Getter for the precision and the rings
	int GetPrecision();
	int GetRings();

	//Objectype setter
	void SetObjectType(ObjectType type);

	//Setter for the wireframe mode
	void SetWireFrameMode(bool);

	//Setter for the uv mode
	void SetTextureMapping(bool);

	//Setter for the face normals rendering
	void SetNormalRendering(bool);

	//Setter for the average normals rendering
	void SetAverageNormals(bool);

	//Setters for the transformations
	void SetPosition(glm::vec3);
	void SetScale(glm::vec3);
	void SetRotation(glm::vec3);

	//Setter of precision and rings
	void SetPrecision(int);
	void SetRings(int);

	//Stores the normals
	std::vector<glm::vec3> Normals;
	GLuint NormalsBuffer;

	std::vector<glm::vec3> AverageNormalsVectors;
	GLuint AverageNormalsVectorBuffer;

	//Update object position
	void UpdatePosition(const glm::vec3 &);

private:

	ObjectType ObjType;

	GLuint VAO;
	GLuint FaceNormalsVAO;
	GLuint AverageNormalsVAO;

	GLuint PositionBufferObject;
	GLuint TextureCoordinatesBuffer;
	GLuint FaceNormalBuffer;
	GLuint AverageNormalBuffer;


	std::vector<glm::vec4> VertexPositions;
	std::vector<glm::vec2> VertexTextureCoordinates;
	std::vector<glm::vec3> FaceNormals;
	std::vector<glm::vec3> AverageNormals;

	bool WireFrameMode;
	bool TextureMapping;
	bool NormalRendering;
	bool AverageNormalsBool;

	int Precision;
	int Rings;

	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;
};