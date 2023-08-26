/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    main.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #2
 \date    06/22/2020
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

GLSLProgram * ShaderProgram;

void InitializeProgram()
{
	if (ShaderProgram != nullptr)
		delete ShaderProgram;

	ShaderProgram = GLSLProgram::CreateShaderProgram("vertex.vs", "fragment.fs");
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

	// Tangents buffer
	glGenBuffers(1, &(shape->TangentsBuffer));

	glBindBuffer(GL_ARRAY_BUFFER, shape->TangentsBuffer);
	glBufferData(GL_ARRAY_BUFFER, shape->tangents.size() * sizeof(glm::vec3), &shape->tangents[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// Bitangents buffer
	glGenBuffers(1, &(shape->BitangentsBuffer));

	glBindBuffer(GL_ARRAY_BUFFER, shape->BitangentsBuffer);
	glBufferData(GL_ARRAY_BUFFER, shape->bitangents.size() * sizeof(glm::vec3), &shape->bitangents[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// VAO Face Normals
	glGenVertexArrays(1, &(shape->GetFaceNormalsVAO()));
	glBindVertexArray(shape->GetFaceNormalsVAO());

	// Normals buffer
	glGenBuffers(1, &(shape->GetNormalsBuffer()));

	glBindBuffer(GL_ARRAY_BUFFER, shape->GetNormalsBuffer());
	glBufferData(GL_ARRAY_BUFFER, shape->GetFaceNormals().size() * sizeof(glm::vec3), &shape->GetFaceNormals()[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// VAO Average Normals
	glGenVertexArrays(1, &(shape->GetAverageNormalsVAO()));
	glBindVertexArray(shape->GetAverageNormalsVAO());

	// Average Normals buffer
	glGenBuffers(1, &(shape->GetAverageNormalsBuffer()));

	glBindBuffer(GL_ARRAY_BUFFER, shape->GetAverageNormalsBuffer());
	glBufferData(GL_ARRAY_BUFFER, shape->GetAverageNormals().size() * sizeof(glm::vec3), &shape->GetAverageNormals()[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// VAO Tangents
	glGenVertexArrays(1, &(shape->TangentsVAO));
	glBindVertexArray(shape->TangentsVAO);

	// Tangents buffer
	glGenBuffers(1, &(shape->TangentsVBO));

	glBindBuffer(GL_ARRAY_BUFFER, shape->TangentsVBO);
	glBufferData(GL_ARRAY_BUFFER, shape->TangentsDraw.size() * sizeof(glm::vec3), &shape->TangentsDraw[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// VAO BitangentsVAO
	glGenVertexArrays(1, &(shape->BitangentsVAO));
	glBindVertexArray(shape->BitangentsVAO);

	// BiTangents buffer
	glGenBuffers(1, &(shape->BitangentsVBO));

	glBindBuffer(GL_ARRAY_BUFFER, shape->BitangentsVBO);
	glBufferData(GL_ARRAY_BUFFER, shape->BitangentsDraw.size() * sizeof(glm::vec3), &shape->BitangentsDraw[0], GL_STATIC_DRAW);

	// Insert the VBO into the VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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

GLuint LoadTexture(const std::string & filename)
{
	SDL_Surface * surface = IMG_Load(filename.c_str());

	if (surface == nullptr)
	{
		std::cout << "Could not load texture: " + filename << std::endl;
		return 0;
	}

	GLuint texture;

	// Create texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Select pixel format from surface
	int pixelFormat = GL_RGB;
	if (surface->format->BytesPerPixel == 4) {
		pixelFormat = GL_RGBA;
	}

	// Give pixel data to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, surface->w, surface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, surface->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	// Free surface because OpenGL already has the data
	SDL_FreeSurface(surface);

	return texture;
}

void cleanup(Object * Shape)
{
	// Delete the VBOs
	glDeleteBuffers(1, &(Shape->GetPositionBufferObject()));
	glDeleteBuffers(1, &(Shape->GetTextureCoordinatesBuffer()));
	glDeleteBuffers(1, &(Shape->NormalsBuffer));
	glDeleteBuffers(1, &(Shape->AverageNormalsVectorBuffer));

	glDeleteBuffers(1, &(Shape->GetNormalsBuffer()));
	glDeleteBuffers(1, &(Shape->GetAverageNormalsBuffer()));

	glDeleteBuffers(1, &(Shape->TangentsVBO));
	glDeleteBuffers(1, &(Shape->BitangentsVBO));

	glDeleteBuffers(1, &(Shape->TangentsBuffer));
	glDeleteBuffers(1, &(Shape->BitangentsBuffer));

	// Delete the VAOs
	glDeleteVertexArrays(1, &(Shape->GetVAO()));
	glDeleteVertexArrays(1, &(Shape->GetFaceNormalsVAO()));
	glDeleteVertexArrays(1, &(Shape->GetAverageNormalsVAO()));
	glDeleteVertexArrays(1, &(Shape->TangentsVAO));
	glDeleteVertexArrays(1, &(Shape->BitangentsVAO));
}

void display(SDL_Window * window, GLsizei Width, GLsizei Height, std::vector<Object*> shape,
GLSLProgram * ShaderProgram, GLuint * textures, Camera & camera, Light * light, Material * material1, Material * material2)
{	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Bind the glsl program and this object's VAO
	ShaderProgram->Use();

	//Bind the texture to Texture units
	for (unsigned i = 0; i < sizeof(textures) / sizeof(textures[0]); i++)
	{
		//Activate the texture unit
		glActiveTexture(GL_TEXTURE0 + i);

		//Bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		std::string textureName = "textureData" + std::to_string(i + 1);
		ShaderProgram->SetUniform(textureName.c_str(), int(i));
	}

	//Set the view matrix
	ShaderProgram->SetUniform("view", camera.GetView());

	//Set the projection matrix
	ShaderProgram->SetUniform("projection", glm::perspective(glm::radians(45.0f), (float)Width / (float)Height, 1.0f, 500.0f));

	//Set the ambient, diffuse and specular light
	ShaderProgram->SetUniform("AmbientLight", light->AmbientLight);

	ShaderProgram->SetUniform("DiffuseLight", light->DiffuseLight);
	
	ShaderProgram->SetUniform("SpecularLight", light->SpecularLight);

	//Set the light position
	if(light->DirectionalLight)
		ShaderProgram->SetUniform("LightPosition", glm::vec3(camera.GetView() * glm::vec4(shape[2]->GetPosition(), 0.0f)));

	else
		ShaderProgram->SetUniform("LightPosition", glm::vec3(camera.GetView() * glm::vec4(shape[2]->GetPosition(), 1.0f)));
	
	//ShaderProgram->SetUniform("LightView", glm::vec3(camera.GetView() * -glm::vec4(shape[2]->GetPosition(), 0.0f)));
	
	//Variables for the the type of ligth
	ShaderProgram->SetUniform("PointLight", light->PointLight);

	ShaderProgram->SetUniform("SpotLight", light->SpotLight);
	
	ShaderProgram->SetUniform("DirectionalLight", light->DirectionalLight);
	
	//Variables for the atenuation
	ShaderProgram->SetUniform("AttenuationC1", light->AttenuationC1);
	
	ShaderProgram->SetUniform("AttenuationC2", light->AttenuationC2);
	
	ShaderProgram->SetUniform("AttenuationC3", light->AttenuationC3);

	//Set the falloff 
	ShaderProgram->SetUniform("FallOff", light->FallOff);

	//Set the inner and outer angle
	ShaderProgram->SetUniform("InnerAngle", cos(glm::radians(light->InnerAngle)));
	ShaderProgram->SetUniform("OuterAngle", cos(glm::radians(light->OuterAngle)));

	//Set render mode
	ShaderProgram->SetUniform("RenderMode", shape[0]->RenderModeCount);

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
		ShaderProgram->SetUniform("model", ModelToWorld);

		//Set the texture
		//ShaderProgram->SetUniform("TextureMapping", shape[i]->GetTextureMapping());

		//Set the bool for the normal rendering to false
		ShaderProgram->SetUniform("NormalRendering", false);

		//Set the first shape material
		if (i == 0)
		{
			ShaderProgram->SetUniform("AmbientMaterial", material1->AmbientMaterial);
			ShaderProgram->SetUniform("DiffuseMaterial", material1->DiffuseMaterial);
			ShaderProgram->SetUniform("SpecularMaterial", material1->SpecularMaterial);
			ShaderProgram->SetUniform("Shininess", material1->ShininessMaterial);
		}

		//Set the second shape material
		else if (i == 1)
		{
			ShaderProgram->SetUniform("AmbientMaterial", material2->AmbientMaterial);
			ShaderProgram->SetUniform("DiffuseMaterial", material2->DiffuseMaterial);
			ShaderProgram->SetUniform("SpecularMaterial", material2->SpecularMaterial);
			ShaderProgram->SetUniform("Shininess", material2->ShininessMaterial);
		}

		if (i == 2)
		{
			ShaderProgram->SetUniform("NormalRendering", true);
			//Set the color
			//ShaderProgram->SetUniform("NormalColor", glm::vec3(1.0f, 1.0f, 1.0f));
		}
		//Wireframe mode enable
		if (shape[i]->GetWireFrameMode())
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Wireframe mode disable
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Bind the vao
		glBindVertexArray(shape[i]->GetVAO());

		//Draw all triangles
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)shape[i]->GetVertexPositions().size() * sizeof(glm::vec3));

		//Set the normal rendering
		ShaderProgram->SetUniform("NormalRendering", shape[i]->GetNormalRendering());

		//Condition where we need to render the normals
		if (shape[i]->GetNormalRendering())
		{
			//Clean the buffers
			cleanup(shape[i]);

			//Initialize the buffer
			InitializeBuffers(shape[i]);

			//Set the color
			ShaderProgram->SetUniform("NormalColor", glm::vec3(0.0f, 0.0f, 1.0f));

			//Condition where we need to render the average normals
			if (shape[i]->GetAverageNormalsBool())
			{
				//Bind the average normals array
				glBindVertexArray(shape[i]->GetAverageNormalsVAO());

				//Draw normals
				glDrawArrays(GL_LINES, 0, (GLsizei)shape[i]->GetAverageNormals().size());

			}

			else
			{
				//Bind the face normals array
				glBindVertexArray(shape[i]->GetFaceNormalsVAO());

				//Draw face normals
				glDrawArrays(GL_LINES, 0, (GLsizei)shape[i]->GetFaceNormals().size());
			}

			//Clean the buffers
			cleanup(shape[i]);

			//Initialize the buffer
			InitializeBuffers(shape[i]);

			//Set the color
			ShaderProgram->SetUniform("NormalColor", glm::vec3(1.0f, 0.0f, 0.0f));

			//Bind the tangents
			glBindVertexArray(shape[i]->TangentsVAO);

			//Draw tangents
			glDrawArrays(GL_LINES, 0, (GLsizei)shape[i]->TangentsDraw.size());

			//Clean the buffers
			cleanup(shape[i]);

			//Initialize the buffer
			InitializeBuffers(shape[i]);

			//Set the color
			ShaderProgram->SetUniform("NormalColor", glm::vec3(0.0f, 1.0f, 0.0f));

			//Bind the bitangents
			glBindVertexArray(shape[i]->BitangentsVAO);

			//Draw bitangents
			glDrawArrays(GL_LINES, 0, (GLsizei)shape[i]->BitangentsDraw.size());
		}
    }

	// Unbind
	glBindVertexArray(0);
	glUseProgram(0);	
	
	//Render imgui data
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());	

	SDL_GL_SwapWindow(window);
}

void Editor(Light * light, Material * material1, Material * material2)
{
	ImGui::Begin("Lights");

	if (ImGui::CollapsingHeader("0"))
	{
		ImGui::ColorEdit3("Ambient", (float*)&light->AmbientLight);
		ImGui::ColorEdit3("Diffuse", (float*)&light->DiffuseLight);
		ImGui::ColorEdit3("Specular", (float*)&light->SpecularLight);

		ImGui::SliderFloat("InnerAngle", &light->InnerAngle, 0.0f, 90.0f);
		ImGui::SliderFloat("OuterAngle", &light->OuterAngle, light->InnerAngle, 90.0f);

		ImGui::SliderFloat("FallOff", &light->FallOff, 0.0f, 100.0f);

		ImGui::SliderFloat("AttenuationC1", &light->AttenuationC1, 0.0f, 10.0f);
		ImGui::SliderFloat("AttenuationC2", &light->AttenuationC2, 0.0f, 0.1f);
		ImGui::SliderFloat("AttenuationC3", &light->AttenuationC3, 0.0f, 0.1f);
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
	GLuint textures[2];

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
	Object * Shape = new Object(Plane);

	//Create the base plane
	Object * BasePlane = new Object(Plane);

	//Create the light
	Object * LightShape = new Object(Sphere);

	//Add the shapes to the vector
	Objects.push_back(Shape);
	Objects.push_back(BasePlane);
	Objects.push_back(LightShape);

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
	Shape->SetScale(glm::vec3(10.0f, 10.0f, 10.0f));

	//Set the position, rotation and scale for the plane
	BasePlane->SetPosition(glm::vec3(0.0f, -15.0f, 0.0f));
	BasePlane->SetRotation(glm::vec3(90.0f * pi / 180.0f  + pi, 0.0f, 0.0f));
	BasePlane->SetScale(glm::vec3(50.0f, 50.0f, 50.0f));

	//Set the position and the scale for the light
	LightShape->SetPosition(glm::vec3(20.0f, 0.0f, 0.0f));
	
	//Initialize the program
	InitializeProgram();

	//Initialize the shapes
	InitializeBuffers(Shape);
	InitializeBuffers(BasePlane);
	InitializeBuffers(LightShape);

	//Create the texture
	textures[0] = CreateProceduralTexture();
	textures[1] = LoadTexture("./textures/normal_map_flippedY.png");

	//Enable culling
	glEnable(GL_CULL_FACE);

	//Culling front face
	glCullFace(GL_BACK);

	//Render clock wise
	glFrontFace(GL_CCW);

	//Angle to rotate the light
	float angle = 0.0f;

	//Pause the light
	bool PauseLight = false;

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

					//Set the shape type
					Shape->SetObjectType(Plane);

					//Compute the plane
					Shape->ComputePlaneVertices();

					//Clean the buffers
					cleanup(Shape);

					//Initialize de buffers
					InitializeBuffers(Shape);

					break;

				//Key 2 for a cube
				case SDLK_2:

					//Set the shape type
					Shape->SetObjectType(Cube);

					//Compute the cube
					Shape->ComputeCubeVertices();

					//Clean the buffers
					cleanup(Shape);

					//Initialize de buffers
					InitializeBuffers(Shape);
					break;

				//Key 3 for a cone
				case SDLK_3:

					//Set the shape type
					Shape->SetObjectType(Cone);

					//Set the precision
					Shape->SetPrecision(19);

					//Compute the cone
					Shape->ComputeConeVertices(Shape->GetPrecision(), -0.001f);

					//Clean the buffers
					cleanup(Shape);

					//Initialize de buffers
					InitializeBuffers(Shape);

					break;


				//Key 4 for a cylinder
				case SDLK_4:

					//Set the shape type
					Shape->SetObjectType(Cylinder);

					//Set the precision
					Shape->SetPrecision(19);

					//Compute the cylinder
					Shape->ComputeCylinderVertices(Shape->GetPrecision(), -0.001f);

					//Clean the buffers
					cleanup(Shape);

					//Initialize de buffers
					InitializeBuffers(Shape);

					break;

				//Key 5 for a sphere
				case SDLK_5:

					//Set the shape type
					Shape->SetObjectType(Sphere);

					//Set the precision
					Shape->SetPrecision(19);

					//Set the sphere rings
					Shape->SetRings(7);

					//Compute the sphere
					Shape->ComputeSphereVertices(Shape->GetPrecision(), Shape->GetRings(), -0.001f);

					//Clean the buffers
					cleanup(Shape);

					//Initialize de buffers
					InitializeBuffers(Shape);

					break;

				//Key 7 for point light
				case SDLK_7:
					Light1->PointLight = true;
					Light1->SpotLight = false;
					Light1->DirectionalLight = false;
					break;

				//Key 8 for spotlight
				case SDLK_8:
					Light1->PointLight = false;
					Light1->SpotLight = true;
					Light1->DirectionalLight = false;
					break;

				//Key 9 for directional light
				case SDLK_9:
					Light1->PointLight = false;
					Light1->SpotLight = false;
					Light1->DirectionalLight = true;
					break;

				//Enable or desable the wireframe mode with M
				case SDLK_m:
					Shape->SetWireFrameMode(!Shape->GetWireFrameMode());
					break;

				//Enable or desable the texture mapping with t
				case SDLK_t:
					Shape->SetTextureMapping(!Shape->GetTextureMapping());

					if (Shape->RenderModeCount == 3)
						Shape->RenderModeCount = 0;

					else
						Shape->RenderModeCount++;

					break;

				//Enable or desable the normal rendering with n
				case SDLK_n:
					Shape->SetNormalRendering(!Shape->GetNormalRendering());

					break;

				//Enable or desable the average normals with f
				case SDLK_f:
					Shape->SetAverageNormals(!Shape->GetAverageNormalsBool());

					if (Shape->GetObjectType() == Cube)
					{
						//Set the shape type
						Shape->SetObjectType(Cube);

						//Compute the cube
						Shape->ComputeCubeVertices();

					}

					else if (Shape->GetObjectType() == Cone)
					{
						//Set the shape type
						Shape->SetObjectType(Cone);

						//Set the precision
						Shape->SetPrecision(19);

						//Compute the cone
						Shape->ComputeConeVertices(Shape->GetPrecision(), -0.001f);

					}

					else if (Shape->GetObjectType() == Cylinder)
					{
						//Set the shape type
						Shape->SetObjectType(Cylinder);

						//Set the precision
						Shape->SetPrecision(19);

						//Compute the cylinder
						Shape->ComputeCylinderVertices(Shape->GetPrecision(), -0.001f);
					}

					else if (Shape->GetObjectType() == Sphere)
					{
						//Set the shape type
						Shape->SetObjectType(Sphere);

						//Set the precision
						Shape->SetPrecision(19);

						//Set the sphere rings
						Shape->SetRings(7);

						//Compute the sphere
						Shape->ComputeSphereVertices(Shape->GetPrecision(), Shape->GetRings(), -0.001f);

					}

					else
					{
						//Set the shape type
						Shape->SetObjectType(Plane);

						//Compute the plane
						Shape->ComputePlaneVertices();
					}
					
					//Clean the buffers
					cleanup(Shape);

					//Initialize de buffers
					InitializeBuffers(Shape);
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

					//Clean the buffers
					cleanup(Shape);

					//Initialize the buffers
					InitializeBuffers(Shape);

					//Increment the precision
					Shape->SetPrecision(Shape->GetPrecision() + 1);

					//Conditions depending the shape
					switch (Shape->GetObjectType())
					{
					case Cone:
						//Compute the cone vertices
						Shape->ComputeConeVertices(Shape->GetPrecision(), -0.001f);
						break;

					case Cylinder:
						//Compute the cylinder vertices
						Shape->ComputeCylinderVertices(Shape->GetPrecision(), -0.001f);
						break;

					case Sphere:
						//Condition when the precision is an even number
						if (Shape->GetPrecision() % 2 == 0)
						{
							//Increment the number of rings
							Shape->SetRings(Shape->GetRings() + 1);
						}
						//Compute the sphere vertices
						Shape->ComputeSphereVertices(Shape->GetPrecision(), Shape->GetRings(), -0.001f);
						break;
					}

					break;

					// Minus key decrement precision
				case SDL_SCANCODE_KP_MINUS:

					//Clean the buffers
					cleanup(Shape);

					//Initialize the buffers
					InitializeBuffers(Shape);

					//Minimum precision for the sphere
					if (Shape->GetPrecision() == 7 && Shape->GetObjectType() == Sphere)
						break;

					//Minimum precision
					else if (Shape->GetPrecision() == 5)
						break;

					//Decrement the precision
					Shape->SetPrecision(Shape->GetPrecision() - 1);

					//Conditions depending the shape
					switch (Shape->GetObjectType())
					{
					case Cone:
						//Compute the cone vertices
						Shape->ComputeConeVertices(Shape->GetPrecision(), 0.001f);
						break;

					case Cylinder:
						//Compute the cylinder vertices
						Shape->ComputeCylinderVertices(Shape->GetPrecision(), 0.001f);
						break;

					case Sphere:
						//Condition when the precision is an even number
						if (Shape->GetPrecision() % 2 == 0)
						{
							//Decrement the number of rings
							Shape->SetRings(Shape->GetRings() - 1);
						}
						//Compute the sphere vertices
						Shape->ComputeSphereVertices(Shape->GetPrecision(), Shape->GetRings(), 0.001f);

						break;
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
			LightShape->UpdatePosition(glm::vec3(0.0f, 0.04f * cosf(angle/ 2.0f), 0.0f));
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		//Set the editor
		Editor(Light1, Material1, Material2);
		
		//Render imgui
		ImGui::Render();

		//Render the shapes
		display(window, WIDTH, HEIGHT, Objects, ShaderProgram, textures, camera, Light1, Material1, Material2);	
	}

	//Shutdown imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//Clean the vaos and vbo
	cleanup(Shape);
	cleanup(BasePlane);
	cleanup(LightShape);

	//Delete the shapes
	delete Shape;
	delete BasePlane;
	delete LightShape;
	delete Light1;
	delete Material1;
	delete Material2;

	//delete ShaderProgram;
	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}