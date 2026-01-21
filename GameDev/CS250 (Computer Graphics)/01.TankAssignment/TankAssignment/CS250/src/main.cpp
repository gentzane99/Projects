/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    main.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #2
 \date    02/11/2020
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
	CameraMode cameramode = RootedCameraMode;

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

	//Creates and renders the window
	sf::RenderWindow window(sf::VideoMode(Width, Height), "CS250 Assignment 3");
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	texture.create(Width, Height);
	image.create(Width, Height, sf::Color::White);

	//Values for the camera distance and height
	float CameraDistance = 100;
	float CameraHeight = 40;

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
	Body.SetTranslation(Point4(0, 0, -100, 1));

	//Sets the scale of the Body
	Body.SetScale(Point4(30, 25, 80, 1));

	//Sets the rotation of the Body
	Body.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Body
	Body.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Body
	Body.ProjectionWindowToViewport(Width, Height);


	//Creates the Turret
	Object Turret;

	//Sets as the Turret parent the body
	Turret.SetParent(Body);

	//Resizes the vector of vertices for the Turret
	Turret.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Turret.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Turret.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the Turret
	Turret.SetTranslation(Point4(0, 20, 0, 1));

	//Sets the scale of the Turret
	Turret.SetScale(Point4(25, 15, 25, 1));

	//Sets the rotation of the Turret
	Turret.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Turret
	Turret.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Turret
	Turret.ProjectionWindowToViewport(Width, Height);


	//Creates the support in which the gun will rotate
	Object GunSupport;

	//Sets as the GunSupport parent the body
	GunSupport.SetParent(Turret);

	//Resizes the vector of vertices for the GunSupport
	GunSupport.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			GunSupport.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];
		}
	}

	//Sets the translation of the GunSupport
	GunSupport.SetTranslation(Point4(0, 0, 12.5, 1));

	//Sets the scale of the GunSupport
	GunSupport.SetScale(Point4(5, 5, 5, 1));

	//Sets the rotation of the GunSupport
	GunSupport.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the GunSupport
	GunSupport.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the GunSupport
	GunSupport.ProjectionWindowToViewport(Width, Height);


	//Creates the gun
	Object Gun;

	//Sets as the Gun parent the body
	Gun.SetParent(GunSupport);

	//Resizes the vector of vertices for the Gun
	Gun.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Gun.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Gun.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the Gun
	Gun.SetTranslation(Point4(0, 0, 20, 1));

	//Sets the scale of the Gun
	Gun.SetScale(Point4(5, 5, 40, 1));

	//Sets the rotation of the Gun
	Gun.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Gun
	Gun.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Gun
	Gun.ProjectionWindowToViewport(Width, Height);


	//Creates the first wheel
	Object Wheel1;

	//Sets as the Wheel1 parent the body
	Wheel1.SetParent(Body);

	//Resizes the vector of vertices for the Wheel1
	Wheel1.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Wheel1.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Wheel1.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the Wheel1
	Wheel1.SetTranslation(Point4(17.5, -12.5, -25, 1));

	//Sets the scale of the Wheel1
	Wheel1.SetScale(Point4(5, 20, 20, 1));

	//Sets the rotation of the Wheel1
	Wheel1.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Wheel1
	Wheel1.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Wheel1
	Wheel1.ProjectionWindowToViewport(Width, Height);


	//Creates the second wheel
	Object Wheel2;

	//Sets as the Wheel2 parent the body
	Wheel2.SetParent(Body);

	//Resizes the vector of vertices for the Wheel2
	Wheel2.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Wheel2.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Wheel2.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the Wheel2
	Wheel2.SetTranslation(Point4(-17.5, -12.5, -25, 1));

	//Sets the scale of the Wheel2
	Wheel2.SetScale(Point4(5, 20, 20, 1));

	//Sets the rotation of the Wheel2
	Wheel2.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Wheel2
	Wheel2.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Wheel2
	Wheel2.ProjectionWindowToViewport(Width, Height);


	//Creates the third wheel
	Object Wheel3;

	//Sets as the Wheel3 parent the body
	Wheel3.SetParent(Body);

	//Resizes the vector of vertices for the Wheel3
	Wheel3.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Wheel3.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Wheel3.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
				(sf::Uint8)CS250Parser::colors[i].y,
				(sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the Wheel3
	Wheel3.SetTranslation(Point4(17.5, -12.5, 25, 1));

	//Sets the scale of the Wheel3
	Wheel3.SetScale(Point4(5, 20, 20, 1));

	//Sets the rotation of the Wheel3
	Wheel3.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Wheel3
	Wheel3.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Wheel3
	Wheel3.ProjectionWindowToViewport(Width, Height);


	//Creates the forth wheel
	Object Wheel4;

	//Sets as the Wheel4 parent the body
	Wheel4.SetParent(Body);

	//Resizes the vector of vertices for the Wheel4
	Wheel4.Vertices.resize(CS250Parser::faces.size() * 3);

	//Goes through all the vertices
	for (unsigned i = 0, k = 0; i < CS250Parser::faces.size(); i++)
	{
		//Goes through the vertices of each face
		for (unsigned j = 0; j < 3; j++, k++)
		{
			//Saves the vertices
			Wheel4.Vertices[k].mPosition = CS250Parser::vertices[CS250Parser::faces[i].indices[j]];

			//Saves the colors
			Wheel4.Vertices[k].mColor = sf::Color((sf::Uint8)CS250Parser::colors[i].x,
											   	  (sf::Uint8)CS250Parser::colors[i].y,
												  (sf::Uint8)CS250Parser::colors[i].z, 255);
		}
	}

	//Sets the translation of the Wheel4
	Wheel4.SetTranslation(Point4(-17.5, -12.5, 25, 1));

	//Sets the scale of the Wheel4
	Wheel4.SetScale(Point4(5, 20, 20, 1));

	//Sets the rotation of the Wheel4
	Wheel4.SetRotation(0, 0, 0);

	//Computes the world to window matrix of the Wheel4
	Wheel4.CameraToProjectionWindow(camera);

	//Computes the window to viewport matrix of the Wheel4
	Wheel4.ProjectionWindowToViewport(Width, Height);



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
			//Rotates the tanks along the y axis
			Body.SetRotation(Body.GetRotationX(), Body.GetRotationY() + 0.1f, Body.GetRotationZ());
		}

		//Checks if the D key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//Rotates the tanks along the y axis
			Body.SetRotation(Body.GetRotationX(), Body.GetRotationY() - 0.1f, Body.GetRotationZ());
		}

		//Checks if the Q key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//Rotates the tanks along the y axis
			Turret.SetRotation(Turret.GetRotationX(), Turret.GetRotationY() + 0.1f, Turret.GetRotationZ());
		}

		//Checks if the E key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//Rotates the tanks along the y axis
			Turret.SetRotation(Turret.GetRotationX(), Turret.GetRotationY() - 0.1f, Turret.GetRotationZ());
		}

		//Checks if the F key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			//Rotates the gunsupport about the x axis
			GunSupport.SetRotation(GunSupport.GetRotationX() + 0.1f, GunSupport.GetRotationY(), GunSupport.GetRotationZ());
		}

		//Checks if the R key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			//Rotates the gunsupport about the x axis
			GunSupport.SetRotation(GunSupport.GetRotationX() - 0.1f, GunSupport.GetRotationY() , GunSupport.GetRotationZ());
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
			//Moves the whole tank in the xz plane
			Body.SetTranslation(Point4(Body.GetTranslation().x + sin(Body.GetRotationY()),
									   Body.GetTranslation().y,
									   Body.GetTranslation().z + cos(Body.GetRotationY()),1));

			//Rotates all the wheels around the X axis
			Wheel1.SetRotation(Wheel1.GetRotationX() + 0.1f, Wheel1.GetRotationY(), Wheel1.GetRotationZ());
			Wheel2.SetRotation(Wheel1.GetRotationX() + 0.1f, Wheel1.GetRotationY(), Wheel1.GetRotationZ());
			Wheel3.SetRotation(Wheel1.GetRotationX() + 0.1f, Wheel1.GetRotationY(), Wheel1.GetRotationZ());
			Wheel4.SetRotation(Wheel1.GetRotationX() + 0.1f, Wheel1.GetRotationY(), Wheel1.GetRotationZ());
		}

		//Condition for the FirstPersonMode
		if (cameramode == FirstPersonMode)
		{
			//Computes the body translation matrix
			Matrix4 BodyTranslation = Matrix4(1, 0, 0, Body.GetTranslation().x,
											  0, 1, 0, Body.GetTranslation().y,
											  0, 0, 1, Body.GetTranslation().z,
											  0, 0, 0, 1);

			//Computes the camera position
			camera.SetCOP(BodyTranslation * Turret.GetTranslation());
	

			//Computes the turret rotation on y
			Matrix4 TurretRotationY = Matrix4(cos(Turret.GetRotationY()), 0, sin(Turret.GetRotationY()), 0,
											 0, 1, 0, 0,
											-sin(Turret.GetRotationY()), 0, cos(Turret.GetRotationY()), 0,
											0, 0, 0, 1);

			//Computes teh camera view vector
			camera.SetViewVector(TurretRotationY * Vector4(0, 0,-1,0));
		}

		//Condition for the ThirdPersonMode
		else if (cameramode == ThirdPersonMode)
		{
			//Computes the body rotation
			Matrix4 RotationMatrixY = Matrix4(cos(Body.GetRotationY()), 0, sin(Body.GetRotationY()), 0,
				0, 1, 0, 0,
				-sin(Body.GetRotationY()), 0, cos(Body.GetRotationY()), 0,
				0, 0, 0, 1);

			//Computes the body forward
			Vector4 TankForward = RotationMatrixY * Vector4(0,0,1,0);
			TankForward.Normalize();

			//Computes the camera position
			camera.SetCOP(Body.GetTranslation() - TankForward * CameraDistance + Vector4(0, 1, 0, 0) * CameraHeight);

			//Computes the camera viewvector
			Vector4 view = Body.GetTranslation() - camera.GetCOP();
			view.Normalize();
			camera.SetViewVector(view);

			//Computes the camera rightvector
			Vector4 right = Vector4(0, 1, 0, 0).Cross(camera.GetViewVector());
			right.Normalize();
			camera.SetRightVector(right);
	
			//Computes the camera upvector
			Vector4 up = camera.GetViewVector().Cross(camera.GetRightVector());
			up.Normalize();
			camera.SetUpVector(up);
			
		}

		//Renders the 25 cubes
		for (unsigned n = 0; n < Cube.size(); n++)
		{
			Cube[n].Render(image, Wireframe, cameramode, camera);
		}

		//Renders the Body
		Body.Render(image, Wireframe, cameramode, camera);

		//Renders the Turret
		Turret.Render(image, Wireframe, cameramode, camera);

		//Renders the Gun
		Gun.Render(image, Wireframe, cameramode, camera);

		//Renders the Wheel1
		Wheel1.Render(image, Wireframe, cameramode, camera);

		//Renders the Wheel2
		Wheel2.Render(image, Wireframe, cameramode, camera);

		//Renders the Wheel3
		Wheel3.Render(image, Wireframe, cameramode, camera);

		//Renders the Wheel4
		Wheel4.Render(image, Wireframe, cameramode, camera);

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