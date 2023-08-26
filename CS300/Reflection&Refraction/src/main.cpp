/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    main.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS300
 \par     Programming Assignment #4
 \date    07/15/2020
 \brief   Main function definition
******************************************************************************/
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object/Object.h"
#include "Camera/Camera.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include "glm/gtx/transform.hpp"
#include "CubeMap/CubeMap.h"

//Create the Shader programs
GLSLProgram * Shader = nullptr;
GLSLProgram * ShaderCubeMap = nullptr;

void InitializeProgram()
{
	// First pass shader program
	if (ShaderCubeMap != nullptr)
		delete ShaderCubeMap;
	ShaderCubeMap = GLSLProgram::CreateShaderProgram("shaders/CubeMap.vs", "shaders/CubeMap.fs");

	// Second pass shader program
	if (Shader != nullptr)
		delete Shader;
	Shader = GLSLProgram::CreateShaderProgram("shaders/vertex.vs", "shaders/fragment.fs");
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
		// Average Normals buffer
		glGenBuffers(1, &(shape->AverageNormalsVectorBuffer));

		glBindBuffer(GL_ARRAY_BUFFER, shape->AverageNormalsVectorBuffer);
		glBufferData(GL_ARRAY_BUFFER, shape->AverageNormalsVectors.size() * sizeof(glm::vec3), &shape->AverageNormalsVectors[0], GL_STATIC_DRAW);

		// Insert the VBO into the VAO
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	else
	{
		// Normals buffer
		glGenBuffers(1, &(shape->NormalsBuffer));

		glBindBuffer(GL_ARRAY_BUFFER, shape->NormalsBuffer);
		glBufferData(GL_ARRAY_BUFFER, shape->Normals.size() * sizeof(glm::vec3), &shape->Normals[0], GL_STATIC_DRAW);

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

void cleanup(Object * Shape, unsigned int CubeMapTexture)
{
	// Delete the VBOs
	glDeleteBuffers(1, &(Shape->GetPositionBufferObject()));
	glDeleteBuffers(1, &(Shape->GetTextureCoordinatesBuffer()));
	glDeleteBuffers(1, &(Shape->NormalsBuffer));
	glDeleteBuffers(1, &(Shape->AverageNormalsVectorBuffer));

	glDeleteBuffers(1, &(Shape->GetNormalsBuffer()));
	glDeleteBuffers(1, &(Shape->GetAverageNormalsBuffer()));

	// Delete the VAOs
	glDeleteVertexArrays(1, &(Shape->GetVAO()));
	glDeleteVertexArrays(1, &(Shape->GetFaceNormalsVAO()));
	glDeleteVertexArrays(1, &(Shape->GetAverageNormalsVAO()));
}

void display(SDL_Window * window, GLsizei Width, GLsizei Height, std::vector<Object*> shape,
 GLuint texture, Camera & camera, CubeMap * cubemap, bool RenderAll)
{
	//Activate the texture unit
	glActiveTexture(GL_TEXTURE0);

	//Set the texture data
	Shader->SetUniform("TextureData", 0);

	//Bind the texture
	glBindTexture(GL_TEXTURE_2D, texture);	

	//Set the refraction index
	Shader->SetUniform("RefractionIndex", cubemap->RefractionIndex);

	//Set camera position
	Shader->SetUniform("CameraPositionWorld", camera.GetCartesianPosition());

	for (unsigned i = 0; i < shape.size(); i++)
	{	
		//Set the render mode
		Shader->SetUniform("RenderMode", shape[i]->RenderMode);
		
		//Dont draw the skybox
		if (i == 3)
			break;

		//Do not render the shaper on the center for the first pass
		if (!RenderAll && i == 0)
			continue;

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
		Shader->SetUniform("model", ModelToWorld);

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
GLuint texture, Camera & camera, unsigned int CubeMapTexture, CubeMap * cubemap)
{	
	//Set the viewport to the environment map size
	glViewport(0, 0, 512, 512);

	//Go throught the faces
	for (unsigned i = 0; i < 6; i++)
	{
		//Bind the faces fbo
		glBindFramebuffer(GL_FRAMEBUFFER, cubemap->cubeFBO[i]);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Render skybox
		glUseProgram(ShaderCubeMap->GetHandle());

		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);

		ShaderCubeMap->Use();
		ShaderCubeMap->SetUniform("view", glm::lookAt(shape[0]->GetPosition(), shape[0]->GetPosition() + cubemap->Front[i], cubemap->Up[i]));
		ShaderCubeMap->SetUniform("projection", glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 1000.0f));

		glBindVertexArray(shape[3]->GetVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glEnable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);

		glUseProgram(0);
		
		//Render the 2 spheres
		glUseProgram(Shader->GetHandle());
		Shader->Use();
		Shader->SetUniform("view", glm::lookAt(shape[0]->GetPosition(), shape[0]->GetPosition() + cubemap->Front[i], cubemap->Up[i]));
		Shader->SetUniform("projection", glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 1000.0f));
		display(window, Width, Height, shape, texture, camera, cubemap, false);

		glUseProgram(0);
	}

	//Render the scene as always

	//Bind the fbo to default
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reset the viewport
	glViewport(0, 0, Width, Height);

	//Render the shapes as always
	glUseProgram(Shader->GetHandle());
	Shader->Use();
	Shader->SetUniform("view", camera.GetView());
	Shader->SetUniform("projection", glm::perspective(glm::radians(60.0f), (float)Width / (float)Height, 0.1f, 500.0f));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->cubemap);
	Shader->SetUniform("EnvironmentMap", 1);

	display(window, Width, Height, shape, texture, camera, cubemap, true);
	glUseProgram(0);

	//Render skybox
	glUseProgram(ShaderCubeMap->GetHandle());

	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);

	ShaderCubeMap->Use();
	ShaderCubeMap->SetUniform("view", glm::mat4(glm::mat3(camera.GetView())));
	ShaderCubeMap->SetUniform("projection", glm::perspective(glm::radians(60.0f), (float)Width / (float)Height, 0.1f, 500.0f));

	glBindVertexArray(shape[3]->GetVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP,CubeMapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glUseProgram(0);

	//Render imgui data
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(window);
}

void Editor(CubeMap * cubemap)
{
	ImGui::Begin("Refraction");

	ImGui::SliderFloat("Refraction Index", &cubemap->RefractionIndex, 1.0f, 10.0f);

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

	//Initialize imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();

	//Vectore with all the objects
	std::vector<Object*> Objects;

	//Create the object
	Object * Shape = new Object(Sphere);

	//Create the object
	Object * SphereLeft = new Object(Sphere);

	//Create the object
	Object * SphereRight = new Object(Sphere);	
	
	//Create the object
	Object * CubeMapObj = new Object(Cube);

	//Add the shapes to the vector
	Objects.push_back(Shape);
	Objects.push_back(SphereLeft);
	Objects.push_back(SphereRight);
	Objects.push_back(CubeMapObj);

	//Create the camera
	Camera camera;

	//Create the texture
	GLuint texture;

	CubeMap * cubemap = new CubeMap();

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
	InitializeBuffers(SphereLeft);
	InitializeBuffers(SphereRight);
	InitializeBuffers(CubeMapObj);

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

	//Pause the spheres
	bool PauseSpheres = false;

	//Create cubemap fbo
	cubemap->FBOCube();

	//Shader configuration
	ShaderCubeMap->Use();
	ShaderCubeMap->SetUniform("Skybox", 0);

	Shader->Use();
	Shader->SetUniform("EnvironmentMap", 0);

	//Load cubemap textures
	GLuint CubemapTexture = cubemap->LoadCubemap(cubemap->FacesCubeMap);
	GLuint CottonCandyTexture = cubemap->LoadCubemap(cubemap->FacesCottonCandy);
	GLuint Save = CubemapTexture;

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
				case SDLK_1:

					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						//Skip with constant shapes
						if (i == 3)
							continue;

						//Set the rotation
						Objects[i]->SetRotation(glm::vec3(0.0f));

						//Set the shape type
						Objects[i]->SetObjectType(Plane);

						//Compute the plane
						Objects[i]->ComputePlaneVertices();

						//Clean the buffers
						cleanup(Objects[i], CubemapTexture);

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
						if (i == 3)
							continue;

						//Set the rotation
						Objects[i]->SetRotation(glm::vec3(0.0f));

						//Set the shape type
						Objects[i]->SetObjectType(Cube);

						//Compute the plane
						Objects[i]->ComputeCubeVertices();

						//Clean the buffers
						cleanup(Objects[i], CubemapTexture);

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
						if (i == 3)
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
						cleanup(Objects[i], CubemapTexture);

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
						if (i == 3)
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
						cleanup(Objects[i], CubemapTexture);

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
						if (i == 3)
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
						cleanup(Objects[i], CubemapTexture);

						//Initialize de buffers
						InitializeBuffers(Objects[i]);
					}

					break;

					//Enable or desable the wireframe mode with M
				case SDLK_m:
					//Go throught the objects
					for (unsigned i = 0; i < Objects.size(); i++)
					{
						if (i == 3)
							continue;

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
						cleanup(Objects[i], CubemapTexture);

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

				//A key pressed
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
					
				//O key pressed
				case SDLK_o:
					PauseSpheres = !PauseSpheres;
					break;				
					
				//Z key pressed
				case SDLK_z:
					Save = CubemapTexture;
					break;				
					
				//X key pressed
				case SDLK_x: 
					Save = CottonCandyTexture;
					break;

				//Chnage render mode
				case SDLK_t:

					if (Shape->RenderMode == 2)
						Shape->RenderMode = 0;

					else
						Shape->RenderMode++;

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
						cleanup(Objects[i], CubemapTexture);

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
						cleanup(Objects[i], CubemapTexture);

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

		//Condition for spheres movement
		if (!PauseSpheres)
		{
			//Update the angle
			angle2 += 0.01f;

			//Spheres movement on y
			SphereLeft->UpdatePosition(glm::vec3(0.0f, 0.04f * cosf(angle2 / 2.0f), 0.0f));
			SphereRight->UpdatePosition(glm::vec3(0.0f, 0.04f * cosf(angle2 / 2.0f), 0.0f));

			SphereLeft->SetPosition(glm::rotate(0.001f, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(SphereLeft->GetPosition(), 1.0f));
			SphereRight->SetPosition(glm::rotate(0.001f, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(SphereRight->GetPosition(), 1.0f));
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		//Set the editor
		Editor(cubemap);

		//Render imgui
		ImGui::Render();

		//Render the shapes
		Render(window, WIDTH, HEIGHT, Objects, texture, camera, Save, cubemap);
	}

	//Shutdown imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//Clean the vaos and vbo
	cleanup(Shape, CubemapTexture);
	cleanup(SphereLeft, CubemapTexture);
	cleanup(SphereRight, CubemapTexture);
	cleanup(CubeMapObj, CubemapTexture);

	//Delete the shapes
	delete Shape;
	delete SphereLeft;
	delete SphereRight;
	delete CubeMapObj;
	delete cubemap;

	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}