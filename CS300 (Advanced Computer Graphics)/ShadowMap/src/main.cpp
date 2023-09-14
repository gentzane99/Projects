/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    main.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #3
 \date    07/06/2020
 \brief   Main function definitiion
******************************************************************************/
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object/Object.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include "glm/gtx/transform.hpp"
#include "ShadowMap/ShadowMap.h"

//Create the Shader programs
GLSLProgram * ShaderProgramFirstPass = nullptr;
GLSLProgram * ShaderProgramSecondPass = nullptr;
GLSLProgram * ShaderProgramShadowMap = nullptr;

void InitializeProgram()
{
	// First pass shader program
	if (ShaderProgramFirstPass != nullptr)
		delete ShaderProgramFirstPass;
	ShaderProgramFirstPass = GLSLProgram::CreateShaderProgram("shaders/shadowmapping.vs", "shaders/shadowmapping.fs");

	// Second pass shader program
	if (ShaderProgramSecondPass != nullptr)
		delete ShaderProgramSecondPass;
	ShaderProgramSecondPass = GLSLProgram::CreateShaderProgram("shaders/vertex.vs", "shaders/fragment.fs");

	// Shadow map shader program
	if (ShaderProgramShadowMap != nullptr)
		delete ShaderProgramShadowMap;
	ShaderProgramShadowMap = GLSLProgram::CreateShaderProgram("shaders/depthquad.vs", "shaders/depthquad.fs");
}

void InitializeBuffers(Object * shape)
{
	// VAO
	glGenVertexArrays(1, &(shape->GetVAO()));
	glBindVertexArray(shape->GetVAO());

	// VBO
	glGenBuffers(1, &(shape->GetPositionBufferObject()));

	//Position buffer
	glBindBuffer(GL_ARRAY_BUFFER, shape->GetPositionBufferObject());
	glBufferData(GL_ARRAY_BUFFER, shape->GetVertexPositions().size() * sizeof(glm::vec4), &shape->GetVertexPositions()[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);


	// Texture coordinate buffer
	glGenBuffers(1, &(shape->GetTextureCoordinatesBuffer()));

	glBindBuffer(GL_ARRAY_BUFFER, shape->GetTextureCoordinatesBuffer());
	glBufferData(GL_ARRAY_BUFFER, shape->GetVertexTextureCoordinates().size() * sizeof(glm::vec2), &shape->GetVertexTextureCoordinates()[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	if (!shape->GetAverageNormalsBool() || shape->GetObjectType() == Plane)
	{
		// Normals buffer
		glGenBuffers(1, &(shape->NormalsBuffer));

		glBindBuffer(GL_ARRAY_BUFFER, shape->NormalsBuffer);
		glBufferData(GL_ARRAY_BUFFER, shape->Normals.size() * sizeof(glm::vec3), &shape->Normals[0], GL_STATIC_DRAW);

		// Insert the VBO into the VAO
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	else
	{
		// Average Normals buffer
		glGenBuffers(1, &(shape->AverageNormalsVectorBuffer));

		glBindBuffer(GL_ARRAY_BUFFER, shape->AverageNormalsVectorBuffer);
		glBufferData(GL_ARRAY_BUFFER, shape->AverageNormalsVectors.size() * sizeof(glm::vec3), &shape->AverageNormalsVectors[0], GL_STATIC_DRAW);

		// Insert the VBO into the VAO
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
}

GLuint CreateProceduralTexture()
{
	GLuint texture;

	// Create texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Color array of the texture
	unsigned char colors[144] = { 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 255, 0, 255, 0, 255, 255, 255, 0, 255, 255, 0, 0, 255,
								255, 0, 0, 255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 255, 0, 255, 0, 255, 255, 255, 0, 255,
								255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 255, 0, 255, 0, 255,
								0, 255, 0, 255, 255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 255,
								0, 255, 255, 255, 0, 255, 0, 255, 255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 0, 0, 255, 255,
								0, 0, 255, 255, 0, 255, 255, 255, 0, 255, 0, 255, 255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255 };

	//Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Give pixel data to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 6, 6, 0, GL_RGBA, GL_UNSIGNED_BYTE, colors);

	return texture;
}

void cleanup(Object * Shape, ShadowMap * shadowMap)
{
	// Delete the VBOs
	glDeleteBuffers(1, &(Shape->GetPositionBufferObject()));
	glDeleteBuffers(1, &(Shape->GetTextureCoordinatesBuffer()));
	glDeleteBuffers(1, &(Shape->NormalsBuffer));
	glDeleteBuffers(1, &(Shape->AverageNormalsVectorBuffer));
	glDeleteBuffers(1, &(shadowMap->QuadVBO));

	// Delete the VAOs
	glDeleteVertexArrays(1, &(Shape->GetVAO()));
	glDeleteVertexArrays(1, &(shadowMap->QuadVAO));
	shadowMap->QuadVAO = 0;
}

void display(SDL_Window * window, GLsizei Width, GLsizei Height, std::vector<Object*> shape,
 GLuint texture, Camera & camera, Light * light, Material * material1, Material * material2)
{
	//Activate the texture unit
	glActiveTexture(GL_TEXTURE0);

	//Bind the texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//Set the texture data
	ShaderProgramSecondPass->SetUniform("TextureData", 0);

	// Bind the glsl program and this object's VAO
	ShaderProgramSecondPass->Use();

	//Set the view matrix
	ShaderProgramSecondPass->SetUniform("view", camera.GetView());
	
	//Set the projection matrix
	ShaderProgramSecondPass->SetUniform("projection", glm::perspective(glm::radians(60.0f), (float)Width / (float)Height, 1.0f, 500.0f));
	
	//Set the Bias
	ShaderProgramSecondPass->SetUniform("Bias", light->Bias);

	//Set the pcf
	ShaderProgramSecondPass->SetUniform("PCFSamples", light->PCFSamples);

	//Set the ambient, diffuse and specular light
	ShaderProgramSecondPass->SetUniform("AmbientLight", light->AmbientLight);

	ShaderProgramSecondPass->SetUniform("DiffuseLight", light->DiffuseLight);

	ShaderProgramSecondPass->SetUniform("SpecularLight", light->SpecularLight);

	//Set the light position
	ShaderProgramSecondPass->SetUniform("LightPosition", glm::vec3(camera.GetView() * glm::vec4(shape[2]->GetPosition(), 1.0f)));

	ShaderProgramSecondPass->SetUniform("LightView", glm::vec3(camera.GetView() * -glm::vec4(shape[2]->GetPosition(), 0.0f)));

	//Variables for the atenuation
	ShaderProgramSecondPass->SetUniform("AttenuationC1", light->AttenuationC1);

	ShaderProgramSecondPass->SetUniform("AttenuationC2", light->AttenuationC2);

	ShaderProgramSecondPass->SetUniform("AttenuationC3", light->AttenuationC3);

	//Set the falloff 
	ShaderProgramSecondPass->SetUniform("FallOff", light->FallOff);

	//Set the inner and outer angle
	ShaderProgramSecondPass->SetUniform("InnerAngle", cos(glm::radians(light->InnerAngle)));
	ShaderProgramSecondPass->SetUniform("OuterAngle", cos(glm::radians(light->OuterAngle)));

	for (unsigned i = 0; i < shape.size(); i++)
	{
		//Set the identity matrix to the model to world
		glm::mat4 ModelToWorld(1.0f);

		//Set the translation from the model to world
		ModelToWorld *= glm::translate(shape[i]->GetPosition());

		//Set the rotation from the model to world
		ModelToWorld *= glm::rotate(shape[i]->GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelToWorld *= glm::rotate(shape[i]->GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelToWorld *= glm::rotate(shape[i]->GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

		//Set the rotation from the scale to world
		ModelToWorld *= glm::scale(shape[i]->GetScale());

		//Set the model matrix
		ShaderProgramSecondPass->SetUniform("model", ModelToWorld);
		ShaderProgramSecondPass->SetUniform("NormalRendering", false);

		//Set the first shape material
		if (i == 0)
		{
			ShaderProgramSecondPass->SetUniform("AmbientMaterial", material1->AmbientMaterial);
			ShaderProgramSecondPass->SetUniform("DiffuseMaterial", material1->DiffuseMaterial);
			ShaderProgramSecondPass->SetUniform("SpecularMaterial", material1->SpecularMaterial);
			ShaderProgramSecondPass->SetUniform("Shininess", material1->ShininessMaterial);
		}

		//Set the second shape material
		else if (i == 1)
		{
			ShaderProgramSecondPass->SetUniform("AmbientMaterial", material2->AmbientMaterial);
			ShaderProgramSecondPass->SetUniform("DiffuseMaterial", material2->DiffuseMaterial);
			ShaderProgramSecondPass->SetUniform("SpecularMaterial", material2->SpecularMaterial);
			ShaderProgramSecondPass->SetUniform("Shininess", material2->ShininessMaterial);
		}

		if (i == 2)
			ShaderProgramSecondPass->SetUniform("NormalRendering", true);


		//Bind the vao
		glBindVertexArray(shape[i]->GetVAO());

		//Wireframe mode enable
		if (shape[i]->GetWireFrameMode())
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Wireframe mode disable
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		//Draw all triangles
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)shape[i]->GetVertexPositions().size() * sizeof(glm::vec3));
	
	}
	// Unbind
	glBindVertexArray(0);
	glUseProgram(0);
}

void Render(SDL_Window * window, GLsizei Width, GLsizei Height, std::vector<Object*> shape,
GLuint texture, Camera & camera, Light * light, Material * material1, Material * material2, ShadowMap * shadowMap)
{	
	//Compute the LightSpaceMatrix
	glm::mat4 LightProjection = glm::perspective(glm::radians(light->OuterAngle * 2.0f), 1.0f, light->Near, light->Far);
	glm::mat4 LightView = glm::lookAt(shape[2]->GetPosition(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 LightSpaceMatrix = LightProjection * LightView;

	ShaderProgramFirstPass->Use();
	ShaderProgramFirstPass->SetUniform("LightSpaceMatrix", LightSpaceMatrix);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//First pass
	glUseProgram(ShaderProgramFirstPass->GetHandle());
	glViewport(0, 0, Width, Height);
	glCullFace(GL_FRONT);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMap->shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (unsigned i = 0; i < shape.size(); i++)
	{
		//Set the identity matrix to the model to world
		glm::mat4 ModelToWorld(1.0f);

		//Set the translation from the model to world
		ModelToWorld *= glm::translate(shape[i]->GetPosition());

		//Set the rotation from the model to world
		ModelToWorld *= glm::rotate(shape[i]->GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelToWorld *= glm::rotate(shape[i]->GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelToWorld *= glm::rotate(shape[i]->GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

		//Set the rotation from the scale to world
		ModelToWorld *= glm::scale(shape[i]->GetScale());

		//Set the model matrix
		ShaderProgramFirstPass->SetUniform("model", ModelToWorld);

		//Bind the vao
		glBindVertexArray(shape[i]->GetVAO());
		
		//Draw all triangles
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)shape[i]->GetVertexPositions().size() * sizeof(glm::vec3));
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glViewport(0, 0, Width, Height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(0);

	//Second pass
	glUseProgram(ShaderProgramSecondPass->GetHandle());
	glCullFace(GL_BACK);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadowMap->depthTex);
	ShaderProgramSecondPass->SetUniform("LightSpaceMatrix", LightSpaceMatrix);
	ShaderProgramSecondPass->SetUniform("ShadowMap", 1);
	ShaderProgramSecondPass->SetUniform("W", glm::inverse(camera.GetView()));
	display(window, Width, Height, shape, texture, camera, light, material1, material2);


	//Render depth map
	glUseProgram(ShaderProgramShadowMap->GetHandle());
	glViewport(0, 0, shadowMap->shadowMapWidth, shadowMap->shadowMapHeight);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadowMap->depthTex);
	ShaderProgramShadowMap->SetUniform("ShadowMapContrast", light->ShadowMapContrast);
	shadowMap->CreadShadowMapQuad();

	glViewport(0, 0, Width, Height);
	glUseProgram(0);

	//Render imgui data
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(window);

}

void Editor(Light * light, Material * material1, Material * material2)
{
	ImGui::Begin("Lights");

	ImGui::SliderFloat("ShadowMap Contrast", &light->ShadowMapContrast, 0.0f, 1.0f);
	
	if (ImGui::CollapsingHeader("0"))
	{
		ImGui::ColorEdit3("Ambient", (float*)&light->AmbientLight);
		ImGui::ColorEdit3("Diffuse", (float*)&light->DiffuseLight);
		ImGui::ColorEdit3("Specular", (float*)&light->SpecularLight);

		ImGui::SliderFloat("InnerAngle", &light->InnerAngle, 0.0f, 89.0f);
		ImGui::SliderFloat("OuterAngle", &light->OuterAngle, light->InnerAngle, 89.0f);

		ImGui::SliderFloat("FallOff", &light->FallOff, 0.0f, 100.0f);

		ImGui::SliderFloat("AttenuationC1", &light->AttenuationC1, 0.0f, 10.0f);
		ImGui::SliderFloat("AttenuationC2", &light->AttenuationC2, 0.001f, 0.1f);
		ImGui::SliderFloat("AttenuationC3", &light->AttenuationC3, 0.001f, 0.1f);

		ImGui::SliderFloat("Near", &light->Near, 0.001f, 100.0f);
		ImGui::SliderFloat("Far", &light->Far, 10.101f, 2000.0f);
		ImGui::SliderFloat("Bias", &light->Bias, 0.0f, 15.0f);
		ImGui::SliderInt("PCFSamples", &light->PCFSamples, 0, 50);
	}

	ImGui::End();

	ImGui::Begin("Materials");

	if (ImGui::CollapsingHeader("0"))
	{
		ImGui::ColorEdit3("Ambient Material 0", (float*)&material1->AmbientMaterial);
		ImGui::ColorEdit3("Diffuse Material 0", (float*)&material1->DiffuseMaterial);
		ImGui::ColorEdit3("Specular Material0", (float*)&material1->SpecularMaterial);
		ImGui::SliderFloat("Shininess Material 0", &material1->ShininessMaterial, 0.1f, 200.0f);
	}

	if (ImGui::CollapsingHeader("1"))
	{
		ImGui::ColorEdit3("Ambient Material 1", (float*)&material2->AmbientMaterial);
		ImGui::ColorEdit3("Diffuse Material 1", (float*)&material2->DiffuseMaterial);
		ImGui::ColorEdit3("Specular Material 1", (float*)&material2->SpecularMaterial);
		ImGui::SliderFloat("Shininess Material 1", &material2->ShininessMaterial, 0.1f, 200.0f);
	}

	ImGui::End();

}

#undef main
int main(int argc, char* args[])
{
	//Window id
	static int winID;

	//Window width and height
	static GLsizei WIDTH = 1280;
	static GLsizei HEIGHT = 720;

	//Create the texture
	GLuint texture;

	//Initialize imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();

	//Create a light
	Light * Light1 = new Light;

	//Create the materials
	Material * Material1 = new Material;
	Material * Material2 = new Material;

	//Vectore with all the objects
	std::vector<Object*> Objects;

	//Create the object
	Object * Shape = new Object(Sphere);

	//Create the base plane
	Object * BasePlane = new Object(Plane);

	//Create the light
	Object * LightShape = new Object(Sphere);

	//Create the object
	Object * SphereLeft = new Object(Sphere);

	//Create the object
	Object * SphereRight = new Object(Sphere);

	//Add the shapes to the vector
	Objects.push_back(Shape);
	Objects.push_back(BasePlane);
	Objects.push_back(LightShape);
	Objects.push_back(SphereLeft);
	Objects.push_back(SphereRight);

	//Create the camera
	Camera camera;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_Window * window = SDL_CreateWindow("CS300", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext context_ = SDL_GL_CreateContext(window);
	if (context_ == nullptr)
	{
		SDL_DestroyWindow(window);
		std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		SDL_GL_DeleteContext(context_);
		SDL_DestroyWindow(window);
		std::cout << "GLEW Error: Failed to init" << std::endl;
		SDL_Quit();
		exit(1);
	}

	ImGui_ImplSDL2_InitForOpenGL(window, context_);
	ImGui_ImplOpenGL3_Init();

	//Set scale for the shape
	Shape->SetScale(glm::vec3(20.0f, 20.0f, 20.0f));
	Shape->SetRotation(glm::vec3(90.0f * pi / 180.0f + pi, 0.0f, 0.0f));

	//Set the position, rotation and scale for the plane
	BasePlane->SetPosition(glm::vec3(0.0f, -15.0f, 0.0f));
	BasePlane->SetRotation(glm::vec3(90.0f * pi / 180.0f + pi, 0.0f, 0.0f));
	BasePlane->SetScale(glm::vec3(100.0f, 100.0f, 100.0f));

	//Set the position for the light
	LightShape->SetPosition(glm::vec3(30.0f, 0.0f, 0.0f));

	//Set the position and scale for the left sphere
	SphereLeft->SetPosition(glm::vec3(-20.0f, 0.0f, 0.0f));
	SphereLeft->SetRotation(glm::vec3(90.0f * pi / 180.0f + pi, 0.0f, 0.0f));
	SphereLeft->SetScale(glm::vec3(5.0f, 5.0f, 5.0f));

	//Set the position and scale for the right sphere
	SphereRight->SetPosition(glm::vec3(20.0f, 0.0f, 0.0f));
	SphereRight->SetRotation(glm::vec3(90.0f * pi / 180.0f + pi, 0.0f, 0.0f));
	SphereRight->SetScale(glm::vec3(5.0f, 5.0f, 5.0f));

	//Initialize the program
	InitializeProgram();

	//Initialize the shapes
	InitializeBuffers(Shape);
	InitializeBuffers(BasePlane);
	InitializeBuffers(LightShape);	
	InitializeBuffers(SphereLeft);
	InitializeBuffers(SphereRight);

	//Create the texture
	texture = CreateProceduralTexture();

	//Enable culling
	glEnable(GL_CULL_FACE);

	//Culling front face
	glCullFace(GL_BACK);

	//Render clock wise
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);

	//Angle to rotate the light
	float angle = 0.0f;

	//Angle to moves the spheres
	float angle2 = 0.0f;

	//Pause the light
	bool PauseLight = false;

	//Pause the spheres
	bool PauseSpheres = false;

	//
	ShadowMap * shadowMap = new ShadowMap;

	//Shader configuration
	ShaderProgramShadowMap->Use();
	ShaderProgramShadowMap->SetUniform("DepthMap", 0);

	//Set up the FBO
	shadowMap->setupFBO(WIDTH, HEIGHT);

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			//Condition when a key is down
			if (event.type == SDL_KEYDOWN)
			{
				//Conditions for keyboard numbers and letters
				switch (event.key.keysym.sym)
				{
					//Key 1 for a plane
				case SDLK_1:

					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Skip with constant shapes
						if (i == 1 || i == 2)
							continue;

						//Set the rotation
						Objects[i]->SetRotation(glm::vec3(0.0f));

						//Set the shape type
						Objects[i]->SetObjectType(Plane);

						//Compute the plane
						Objects[i]->ComputePlaneVertices();

						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize de buffers
						InitializeBuffers(Objects[i]);
					}

					break;

					//Key 2 for a cube
				case SDLK_2:

					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Skip with constant shapes
						if (i == 1 || i == 2)
							continue;

						//Set the rotation
						Objects[i]->SetRotation(glm::vec3(0.0f));

						//Set the shape type
						Objects[i]->SetObjectType(Cube);

						//Compute the plane
						Objects[i]->ComputeCubeVertices();

						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize de buffers
						InitializeBuffers(Objects[i]);
					}

					break;

					//Key 3 for a cone
				case SDLK_3:

					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Skip with constant shapes
						if (i == 1 || i == 2)
							continue;

						//Set the rotation
						Objects[i]->SetRotation(glm::vec3(0.0f));

						//Set the shape type
						Objects[i]->SetObjectType(Cone);

						//Set the precision
						Objects[i]->SetPrecision(19);

						//Compute the plane
						Objects[i]->ComputeConeVertices(Objects[i]->GetPrecision(), -0.001f);

						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize de buffers
						InitializeBuffers(Objects[i]);
					}

					break;


					//Key 4 for a cylinder
				case SDLK_4:

					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Skip with constant shapes
						if (i == 1 || i == 2)
							continue;

						//Set the rotation
						Objects[i]->SetRotation(glm::vec3(0.0f));

						//Set the shape type
						Objects[i]->SetObjectType(Cylinder);

						//Set the precision
						Objects[i]->SetPrecision(19);

						//Compute the plane
						Objects[i]->ComputeCylinderVertices(Objects[i]->GetPrecision(), -0.001f);

						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize de buffers
						InitializeBuffers(Objects[i]);
					}

					break;

					//Key 5 for a sphere
				case SDLK_5:

					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Skip with constant shapes
						if (i == 1 || i == 2)
							continue;

						//Set the rotation
						Objects[i]->SetRotation(glm::vec3(90.0f * pi / 180.0f + pi, 0.0f, 0.0f));

						//Set the shape type
						Objects[i]->SetObjectType(Sphere);

						//Set the precision
						Objects[i]->SetPrecision(19);

						//Set the sphere rings
						Objects[i]->SetRings(7);

						//Compute the plane
						Objects[i]->ComputeSphereVertices(Objects[i]->GetPrecision(), Objects[i]->GetRings(), -0.001f);

						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize de buffers
						InitializeBuffers(Objects[i]);
					}

					break;

					//Enable or desable the wireframe mode with M
				case SDLK_m:
					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						Objects[i]->SetWireFrameMode(!Objects[i]->GetWireFrameMode());
					}
					break;

					//Enable or desable the average normals with f
				case SDLK_f:
					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						Objects[i]->SetAverageNormals(!Objects[i]->GetAverageNormalsBool());

						if (Objects[i]->GetObjectType() == Cube)
						{
							//Set the shape type
							Objects[i]->SetObjectType(Cube);

							//Compute the cube
							Objects[i]->ComputeCubeVertices();

						}

						else if (Objects[i]->GetObjectType() == Cone)
						{
							//Set the shape type
							Objects[i]->SetObjectType(Cone);

							//Set the precision
							Objects[i]->SetPrecision(19);

							//Compute the cone
							Objects[i]->ComputeConeVertices(Objects[i]->GetPrecision(), -0.001f);

						}

						else if (Objects[i]->GetObjectType() == Cylinder)
						{
							//Set the shape type
							Objects[i]->SetObjectType(Cylinder);

							//Set the precision
							Objects[i]->SetPrecision(19);

							//Compute the cylinder
							Objects[i]->ComputeCylinderVertices(Objects[i]->GetPrecision(), -0.001f);
						}

						else if (Objects[i]->GetObjectType() == Sphere)
						{
							//Set the shape type
							Objects[i]->SetObjectType(Sphere);

							//Set the precision
							Objects[i]->SetPrecision(19);

							//Set the sphere rings
							Objects[i]->SetRings(7);

							//Compute the sphere
							Objects[i]->ComputeSphereVertices(Objects[i]->GetPrecision(), Objects[i]->GetRings(), -0.001f);

						}

						else
						{
							//Set the shape type
							Objects[i]->SetObjectType(Plane);

							//Compute the plane
							Objects[i]->ComputePlaneVertices();
						}

						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize de buffers
						InitializeBuffers(Objects[i]);
					}
					break;

					//Q key pressed
				case SDLK_q:
					//Closer to the object
					camera.SetRadius(camera.GetRadius() - 0.5f);
					camera.UpdateView();
					break;

					//E key pressed
				case SDLK_e:
					//Further to the object
					camera.SetRadius(camera.GetRadius() + 0.5f);
					camera.UpdateView();
					break;

					//Akey pressed
				case SDLK_a:
					camera.SetAzimuth(camera.GetAzimuth() + 0.05f);
					camera.UpdateView();

					break;

					//D key pressed
				case SDLK_d:
					camera.SetAzimuth(camera.GetAzimuth() - 0.05f);
					camera.UpdateView();

					break;

					//W key pressed
				case SDLK_w:
					camera.SetLatitude(camera.GetLatitude() - 0.05f);
					camera.UpdateView();
					break;

					//S key pressed
				case SDLK_s:
					camera.SetLatitude(camera.GetLatitude() + 0.05f);
					camera.UpdateView();
					break;

					//P key pressed
				case SDLK_p:
					PauseLight = !PauseLight;	
					break;
					
				//O key pressed
				case SDLK_o:
					PauseSpheres = !PauseSpheres;
					break;
				}

				//Condition for arrows in the keyboard
				switch (event.key.keysym.scancode)
				{
					//Up arrow
				case SDL_SCANCODE_UP:
					//Rotate on x axis
					Shape->SetRotation(Shape->GetRotation() + glm::vec3(2.1f * pi / 180.0f, 0.0f, 0.0f));
					break;

					//Down arrow
				case SDL_SCANCODE_DOWN:
					//Rotate on x axis
					Shape->SetRotation(Shape->GetRotation() + glm::vec3(-2.1f * pi / 180.0f, 0.0f, 0.0f));
					break;

					//Left arrow
				case SDL_SCANCODE_LEFT:
					//Rotate on y axis
					Shape->SetRotation(Shape->GetRotation() + glm::vec3(0.0f, -2.1f * pi / 180.0f, 0.0f));

					break;

					//Right arrow
				case SDL_SCANCODE_RIGHT:
					//Rotate on y axis
					Shape->SetRotation(Shape->GetRotation() + glm::vec3(0.0f, 2.1f * pi / 180.0f, 0.0f));
					break;

					// Plus key increment precision
				case SDL_SCANCODE_KP_PLUS:
					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize the buffers
						InitializeBuffers(Objects[i]);

						//Increment the precision
						Objects[i]->SetPrecision(Objects[i]->GetPrecision() + 1);

						//Conditions depending the shape
						switch (Objects[i]->GetObjectType())
						{
						case Cone:
							//Compute the cone vertices
							Objects[i]->ComputeConeVertices(Objects[i]->GetPrecision(), -0.001f);
							break;

						case Cylinder:
							//Compute the cylinder vertices
							Objects[i]->ComputeCylinderVertices(Objects[i]->GetPrecision(), -0.001f);
							break;

						case Sphere:
							//Condition when the precision is an even number
							if (Objects[i]->GetPrecision() % 2 == 0)
							{
								//Increment the number of rings
								Objects[i]->SetRings(Objects[i]->GetRings() + 1);
							}
							//Compute the sphere vertices
							Objects[i]->ComputeSphereVertices(Objects[i]->GetPrecision(), Objects[i]->GetRings(), -0.001f);
							break;
						}
					}
					break;

					// Minus key decrement precision
				case SDL_SCANCODE_KP_MINUS:

					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Clean the buffers
						cleanup(Objects[i], shadowMap);

						//Initialize the buffers
						InitializeBuffers(Objects[i]);

						//Minimum precision for the sphere
						if (Objects[i]->GetPrecision() == 7 && Objects[i]->GetObjectType() == Sphere)
							break;

						//Minimum precision
						else if (Objects[i]->GetPrecision() == 5)
							break;

						//Decrement the precision
						Objects[i]->SetPrecision(Objects[i]->GetPrecision() - 1);

						//Conditions depending the shape
						switch (Objects[i]->GetObjectType())
						{
						case Cone:
							//Compute the cone vertices
							Objects[i]->ComputeConeVertices(Objects[i]->GetPrecision(), 0.001f);
							break;

						case Cylinder:
							//Compute the cylinder vertices
							Objects[i]->ComputeCylinderVertices(Objects[i]->GetPrecision(), 0.001f);
							break;

						case Sphere:
							//Condition when the precision is an even number
							if (Objects[i]->GetPrecision() % 2 == 0)
							{
								//Decrement the number of rings
								Objects[i]->SetRings(Objects[i]->GetRings() - 1);
							}
							//Compute the sphere vertices
							Objects[i]->ComputeSphereVertices(Objects[i]->GetPrecision(), Objects[i]->GetRings(), 0.001f);

							break;
						}
					}
					break;
				}
			}

			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}

		}

		//Condition for light movement
		if (!PauseLight)
		{
			//Angle increment
			angle += 0.01f;

			//Light movement on x and z
			LightShape->SetPosition(glm::rotate(0.001f, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(LightShape->GetPosition(), 1.0f));

			//Light movement on y
			LightShape->UpdatePosition(glm::vec3(0.0f, 0.04f * cosf(angle / 2.0f), 0.0f));
		}


		//Condition for spheres movement
		if (!PauseSpheres)
		{
			//Update the angle
			angle2 += 0.01f;

			//Spheres movement on y
			SphereLeft->UpdatePosition(glm::vec3(0.0f, 0.04f * cosf(angle2 / 2.0f), 0.0f));
			SphereRight->UpdatePosition(glm::vec3(0.0f, 0.04f * cosf(angle2 / 2.0f), 0.0f));
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		//Set the editor
		Editor(Light1, Material1, Material2);

		//Render imgui
		ImGui::Render();

		//Render the shapes
		Render(window, WIDTH, HEIGHT, Objects, texture, camera, Light1, Material1, Material2, shadowMap);
	}

	//Shutdown imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//Clean the vaos and vbo
	cleanup(Shape, shadowMap);
	cleanup(BasePlane, shadowMap);
	cleanup(LightShape, shadowMap);
	cleanup(SphereLeft, shadowMap);
	cleanup(SphereRight, shadowMap);

	//Delete the shapes
	delete Shape;
	delete BasePlane;
	delete LightShape;
	delete Light1;
	delete Material1;
	delete Material2;
	delete SphereLeft;
	delete SphereRight;
	delete shadowMap;

	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}