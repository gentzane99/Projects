/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    main.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #4
 \date    02/19/2020
 \brief   Main function definition
******************************************************************************/

#include "Object/Object.h"

/*!****************************************************************************
 \brief main function with the main loop
 \return int - 0 
******************************************************************************/
int main()
{	
	//Reads the values of the input file
	CS250Parser::LoadDataFromFile();
	
	//Variable to store the width and the height of the window
	int Width = 1280;
	int Height = 800;

	//Variable to set the Wireframe on or off
	bool Wireframe = false;

	//Creates a variable to store the current camera mode
	CameraMode cameramode = ThirdPersonMode;

	//Pointer to the camera
	Camera camera;

	//Sets the camera vector
	camera.SetCOP(Point4(0, 0, 0, 1));
	camera.SetUpVector(Vector4(0, 1, 0, 0));
	camera.SetViewVector(Vector4(0, 0, -1, 0));
	camera.SetRightVector(camera.GetViewVector().Cross(camera.GetUpVector()));

	//Sets the camera focal lenght and other values
	camera.SetFocalLength(CS250Parser::focal);
	camera.SetBottom(CS250Parser::bottom);
	camera.SetTop(CS250Parser::top);
	camera.SetRight(CS250Parser::right);
	camera.SetLeft(CS250Parser::left);
	camera.SetNearPlane(CS250Parser::nearPlane);
	camera.SetFarPlane(CS250Parser::farPlane);

	//Creates the depth buffer
	std::vector<float> ZBuffer;

	//Resizes the depth buffer
	ZBuffer.resize(Width * Height);

	//Creates and renders the window
	sf::RenderWindow window(sf::VideoMode(Width, Height), "CS250 Assignment 5");
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	texture.create(Width, Height);
	image.create(Width, Height, sf::Color::White);

	//Values for the camera distance and height
	float CameraDistance = 100;
	float CameraHeight = 50;

	//Creates a vector of Cube
	std::vector<Object>Cube;

	//Number of cubes
	int n = 0;

	//Resizes the number of cubes
	Cube.resize(25);

	//Goes through the x coordinates
	for (float x = -100; x <= 100; x += 50)
	{
		//Goes through the z coordinates
		for (float z = 100; z >= -100; z -= 50, n++)
		{	
			//Resizes the vector of vertices for the Cube
			Cube[n].Vertices.resize(CS250Parser::faces.size() * 3);

			//Goes through all the vertices
			for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
			{
				//Goes through the vertices of each face
				for (unsigned j = 0; j < 3; j++, k++)
				{
					//Saves the vertices
					Cube[n].Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

					//Saves the colors
					Cube[n].Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
						(sf::Uint8)CS250Parser::colors[i].y,
						(sf::Uint8)CS250Parser::colors[i].z, 255);
				}
			}


			//Sets the translations of the Cube
			Cube[n].SetTranslation(Point4(x, 0, -z, 1));

			//Sets the scale of the Body
			Cube[n].SetScale(Point4(10, 10, 10, 1));

			//Sets the rotation of the Cube
			Cube[n].SetRotation(0, 0, 0);

			//Computes the world to window matrix of the Cube
			Cube[n].CameraToProjectionWindow(camera);

			//Computes the window to viewport matrix of the Cube
			Cube[n].ProjectionWindowToViewport(Width, Height);
		}
	}

		
	//Creates the Body
	Object Body;

	//Resizes the vector of vertices for the Body
	Body.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Body.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Body.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translations of the Body
	Body.SetTranslation(Point4(0, 0, -50, 1));

	//Sets the scale of the Body
	Body.SetScale(Point4(15, 12.5, 40, 1));

	//Sets the rotation of the Body
	Body.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Body
	Body.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Body
	Body.ProjectionWindowToViewport(Width, Height);


	//Creates the Tail
	Object Tail;

	//Sets as the Tail parent the body
	Tail.SetParent(Body);

	//Resizes the vector of vertices for the Tail
	Tail.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Tail.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Tail.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the Tail
	Tail.SetTranslation(Point4(0, 10, -15, 1));

	//Sets the scale of the Tail
	Tail.SetScale(Point4(5, 7.5, 10, 1));

	//Sets the rotation of the Tail
	Tail.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Tail
	Tail.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Tail
	Tail.ProjectionWindowToViewport(Width, Height);

	//Creates the left wing
	Object LeftWing;

	//Sets as the LeftWing parent the body
	LeftWing.SetParent(Body);

	//Resizes the vector of vertices for the LeftWing
	LeftWing.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			LeftWing.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			LeftWing.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the LeftWing
	LeftWing.SetTranslation(Point4(-17.5, 0, 0, 1));

	//Sets the scale of the LeftWing
	LeftWing.SetScale(Point4(20, 5, 10, 1));

	//Sets the rotation of the LeftWing
	LeftWing.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the LeftWing
	LeftWing.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the LeftWing
	LeftWing.ProjectionWindowToViewport(Width, Height);


	//Creates the right wing
	Object RightWing;

	//Sets as the RightWing parent the body
	RightWing.SetParent(Body);

	//Resizes the vector of vertices for the RightWing
	RightWing.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			RightWing.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			RightWing.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the RightWing
	RightWing.SetTranslation(Point4(17.5, 0, 0, 1));

	//Sets the scale of the RightWing
	RightWing.SetScale(Point4(20, 5, 10, 1));

	//Sets the rotation of the RightWing
	RightWing.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the RightWing
	RightWing.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the RightWing
	RightWing.ProjectionWindowToViewport(Width, Height);

	//Main loop when the window is open
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Checks if the Escape key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//Closes de window
			window.close();
		}

		//Checks if the 1 key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			//Sets the Wireframe mode to false
			Wireframe = false;
		}

		//Checks if the 2 key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			//Sets the Wireframe mode to true
			Wireframe = true;
		}

		//Checks if the 3 key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			//Sets the first person mode
			cameramode = FirstPersonMode;
		}

		//Checks if the 4 key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			//Sets the third person mode
			cameramode = ThirdPersonMode;
		}

		//Checks if the 5 key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			//Sets the rooted camera mode
			cameramode = RootedCameraMode;
			camera.SetCOP(Point4(0, 0, 0, 1));
			camera.SetUpVector(Vector4(0, 1, 0, 0));
			camera.SetViewVector(Vector4(0, 0, -1, 0));
			camera.SetRightVector(camera.GetViewVector().Cross(camera.GetUpVector()));
		}

		//Checks if the A key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//Computes the AxisAngleMethod around the Forward vector 
			Body.AxisAngleMethod(Body.Forward, -0.02f);

			//Update the Up vector
			Body.Up = Body.AxisAngleMethodMatrix * Body.Up;

			//Update the Right vector
			Body.Right = Body.AxisAngleMethodMatrix * Body.Right;

			//Rotates the airplane along the z axis, rolls tha airplane
			Body.SetRotation(Body.GetRotationX(), Body.GetRotationY(), Body.GetRotationZ() - 0.02f);
		}

		//Checks if the D key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//Computes the AxisAngleMethod around the Forward vector 
			Body.AxisAngleMethod(Body.Forward, 0.02f);

			//Update the Up vector
			Body.Up = Body.AxisAngleMethodMatrix * Body.Up;

			//Update the Right vector
			Body.Right = Body.AxisAngleMethodMatrix * Body.Right;

			//Rotates the airplane along the z axis, rolls tha airplane
			Body.SetRotation(Body.GetRotationX(), Body.GetRotationY() , Body.GetRotationZ() + 0.02f);
		}

		//Checks if the Q key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//Computes the AxisAngleMethod around the up vector 
			Body.AxisAngleMethod(Body.Up, 0.02f);

			//Update the forward vector
			Body.Forward = Body.AxisAngleMethodMatrix * Body.Forward;

			//Update the right vector
			Body.Right = Body.AxisAngleMethodMatrix * Body.Right;

			//Rotates the airplane along the y axis, yaws the airplane
			Body.SetRotation(Body.GetRotationX(), Body.GetRotationY() + 0.02f, Body.GetRotationZ());
		}

		//Checks if the E key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//Computes the AxisAngleMethod around the up vector 
			Body.AxisAngleMethod(Body.Up, -0.02f);

			//Update the forward vector
			Body.Forward = Body.AxisAngleMethodMatrix * Body.Forward;

			//Update the Right vector
			Body.Right = Body.AxisAngleMethodMatrix * Body.Right;

			//Rotates the airplane along the y axis, yaws the airplane
			Body.SetRotation(Body.GetRotationX(), Body.GetRotationY() - 0.02f, Body.GetRotationZ());
		}

		//Checks if the W key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//Computes the AxisAngleMethod around the right vector 
			Body.AxisAngleMethod(Body.Right, -0.02f);

			//Update the forward vector
			Body.Forward = Body.AxisAngleMethodMatrix * Body.Forward;

			//Update the up vector
			Body.Up = Body.AxisAngleMethodMatrix * Body.Up;

			//Rotates the airplane along the x axis, pitches the airplane
			Body.SetRotation(Body.GetRotationX() - 0.02f, Body.GetRotationY(), Body.GetRotationZ());
		}

		//Checks if the S key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//Computes the AxisAngleMethod around the right vector 
			Body.AxisAngleMethod(Body.Right, 0.02f);

			//Update the forward vector
			Body.Forward = Body.AxisAngleMethodMatrix * Body.Forward;

			//Update the up vector
			Body.Up = Body.AxisAngleMethodMatrix * Body.Up;

			//Rotates the airplane along the x axis, pitches the airplane
			Body.SetRotation(Body.GetRotationX() + 0.02f, Body.GetRotationY() , Body.GetRotationZ());
		}

		//Checks if the Z key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			//Decreases the camera matrix
			CameraDistance--;
		}

		//Checks if the X key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			//Increases the camera matrix
			CameraDistance++;
		}

		//Checks if the H key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			//Decrease camera height
			CameraHeight--;
		}

		//Checks if the Y key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			//Increase camera height
			CameraHeight++;
		}

		//Checks if the Space key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
  			Body.SetTranslation(Body.GetTranslation() + Body.Forward * 0.2);
		}

		//Condition for the FirstPersonMode
		if (cameramode == FirstPersonMode)
		{
			//Computes the camera position
			camera.SetCOP(Body.GetTranslation());

			Body.Up.Normalize();

			//Computes the camera up vector
			camera.SetUpVector(Body.Up);

			Body.Forward.Normalize();

			//Computes the camera view vector
			camera.SetViewVector(Body.Forward);
			
			Body.Right.Normalize();

			//Computes the camera right vector
			camera.SetRightVector(Body.Right);
		}

		//Condition for the ThirdPersonMode
		else if (cameramode == ThirdPersonMode)
		{
			//Computes the camera position
			camera.SetCOP(Body.GetTranslation() - Body.Forward * CameraDistance + Body.Up * CameraHeight);

			//Computes the camera viewvector
			Vector4 view = Body.GetTranslation() - camera.GetCOP();
			view.Normalize();
			camera.SetViewVector(view);			
			
			//Computes the camera rightvector
			Vector4 right = camera.GetViewVector().Cross(Body.Up);
			right.Normalize();
			camera.SetRightVector(right);
				
			//Computes the camera upvector
			Vector4 up = camera.GetRightVector().Cross(camera.GetViewVector());
			up.Normalize();
			camera.SetUpVector(up);
			
		}

		//Clear the depth buffer
		for (int i = 0; i < Width * Height; i++)
		{
			ZBuffer[i] = 1;
		}

		//Renders the 25 cubes
		for (unsigned n = 0; n < Cube.size(); n++)
		{
			Cube[n].Render(image, Wireframe, cameramode, camera, ZBuffer);
		}

		//Renders the Body
		Body.Render(image, Wireframe, cameramode, camera, ZBuffer);

		//Renders the Tail
		Tail.Render(image, Wireframe, cameramode, camera, ZBuffer);

		//Renders the LeftWing
		LeftWing.Render(image, Wireframe, cameramode, camera, ZBuffer);

		//Renders the RightWing
		RightWing.Render(image, Wireframe, cameramode, camera, ZBuffer);

		//Clears the window and updates the frame buffer
		window.clear();
		texture.update(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();

		//Sets all the pixel of the screen to the default color
		image.create(Width, Height, sf::Color::White);
	}

	return 0;
}