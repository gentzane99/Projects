/******************************************************************************
filename    main.c
author      Gentzane Pastor
DP email    gentzane.pastor@digipen.edu
course      CS120  
project     final
due date    04/27/2018

Brief Description: 
Main for Galacters.
******************************************************************************/
#include <stdio.h>  /*printf, scanf*/
#include <windows.h> /*system*/
#include <conio.h>/*getch*/
#include "GalactersDefines.h" /*Defines*/
#include "GalactersFunctions.h"/*Function declarations*/

int main(void)
{
	int direction = 0; /*Variable for the direction of the enemies*/
	int down = 0; /*Variables for the enemies to move down*/
	int TotalEnemies = 0; /*Variable to count the total enemies*/
	int EnemyLaser = 4; /*Variable to load the enemy shoot*/
	int gamemode = 0; /*Variable to store the gamemode*/
	int lifes = 0;/*Variable for the number of lifes of the player*/
	int powerup = 0;/*Variable to store the powerup*/
	int pickedPw = 0;/*Variable to determine if the power up is picked*/
	int save = 0; /*Variable to save the returns of player movement*/
	int save2 = 0;/*Variable to save the returns of player bullet*/
	int score = 0;/*Variable to store the score earned*/
	int space = 0;/*Variable to know if the space was pressed*/
	char spaceship = SPACESHIP;/*Variable to store the type of spaceship*/
	/*Variable to randomize the frame where the powerup will appear */
	int freeze = (rand() % (50 + 1 - 30)) + 30; 
	char name[20] = {0};/*Array for the name of the player*/
	char Space[SPACE_HEIGHT][SPACE_WIDTH];/*Array for the Space*/

	/*Seed for the random number*/
	srand(time(0));

	/*Calls the fucnction that creates the space*/
	CreateSpace(Space, SPACE_HEIGHT, SPACE_WIDTH, WHITE_SPACE);

	/*Sets the color to green*/
	system("color A");

	/*Ask for the name of the player and the game mode 
	(with some pauses between the prints)*/
	Sleep(1000);
	printf("Welcome to GALACTERS!\n");
	Sleep(1100);
	printf("Enter your name please: ");
	gets(name);
	printf("Hi %s!\n",name);
	Sleep(1200);
	printf("Choose a game mode to continue: \n");
	Sleep(100);
	printf("Practice mode (1), Easy mode (2), Normal mode (3), Hard mode (4):\n");
	gamemode = _getch();
	Sleep(1200);

	/*Condition where the game mode is 1 or 2*/
	if ((gamemode == '1') || (gamemode == '2'))
	{
		/*Calls the function that adds only one type of enemy*/
		TotalEnemies = AddEnemy(Space, SPACE_WIDTH);
	}
	/*Condition where the game mode is 3 or 4*/
	else if ((gamemode == '3') || (gamemode == '4'))
	{
		/*Calls the function that adds both types of enemies*/
		TotalEnemies = AddAllEnemies(Space, SPACE_WIDTH);
	}

	/*Condition where the input for the gamemode is different to
	the ones stated. Closes the game*/
	else
		return 0;

	/*Condition where the game mode is different to 4, lifes will set to 3*/
	if (gamemode != '4')
		lifes = 3;
	/*Condition where the gamemode is 4, lifes will be set to 1*/
	else
		lifes = 1;

	/*If the gamemode is not the Easy mode*/
	if (gamemode != '2')
	{
		/*Asks the user to choose a space type
		(with some pauses between the prints)*/
		printf("Choose a type of space ship to start:\n");
		Sleep(100);
		printf("Normal Spaceship (1), Speedy Spaceship (2), Healthy Spaceship (3):\n");
		spaceship = _getch();
		Sleep(1200);

		/*Condition where the spaceship chosen is 1*/
		if (spaceship == '1')
		{
			/*Sets the type of the normal spaceship*/
			spaceship = SPACESHIP;
		}

		/*Condition where the spaceship chosen is 2*/
		else if (spaceship == '2')
		{
			/*Sets the type of the speedy spaceship*/
			spaceship = SPEEDY_SPACESHIP;
		}
		/*Condition where the spaceship chosen is 3*/
		else if (spaceship == '3')
		{
			/*Sets the type of the healthy spaceship*/
			spaceship = HEALTHY_SPACESHIP;
			/*Adds one to the number of lifes*/
			lifes++;
		}

		/*Condition where the input for the gamemode is different to
		the ones stated. Closes the game*/
		else
			return 0;
	}

	/*Adds the player and the shields for the player*/
    AddPlayer(Space, SPACESHIP_X,SPACESHIP_Y, spaceship);
	AddShields(Space, SPACE_HEIGHT, SPACE_WIDTH);

	/*Gameloop*/
    while(1)
    {
		/*Condition where the freeze counter is 0*/
		if (freeze == 0)
		{
			/*Sets the power up and calls the function adds it*/
			powerup = FREEZY_PU;
			AddPowerUP(Space, SPACE_HEIGHT, powerup);
		}

		/*Clears the screen*/
		system("clear");
		
		/*Prints the Space*/
		PrintSpace(Space, SPACE_HEIGHT, SPACE_WIDTH);
		
		/*Prints the current number of lifes and the score*/
		printf("Number of lifes: %i", lifes);
		printf("                         Score: %i", score);

		/*Condition where the powerup was not picked*/
		if (pickedPw == 0)
		{
			/*Enemies will be able to move*/
			EnemyMovement(Space, SPACE_HEIGHT, SPACE_WIDTH, &direction, &down);
		}

		/*Saves the returns of PlayerMovement and Bullet*/
		save = PlayerMovement(Space, SPACE_HEIGHT, SPACE_WIDTH, spaceship);
		save2 = Bullet(Space, SPACE_HEIGHT, SPACE_WIDTH, &TotalEnemies);
		
		/*Condition where the function Bullet is 2 (death of a superenemy)*/
		if (save2 == 2)
		{
			/*Adds 20 to the score*/
			score+=20;
		}

		/*Condition where the function Bullet is 1 (player wins)*/
		else if (save2 == 1)
		{
			/*Prints the total score of the player and exist the game when any key 
			is pressed*/
			printf("\nCongratulations %s you have defeated all the enemies\n", name);
			Sleep(1200);
			printf("Total score: %i",score);
			Sleep(1200);
			printf("\nPress SPACE to quit");
			space=_getch();

			return 0;
		}

		/*Condition where the function Bullet is 2 (death of an enemy)*/
		else if (save2 == 3)
		{
			/*Adds 20 to the score*/
			score += 20;
		}

		/*Condition where the PlayerMovement is 1(player died)*/
		if (save == 1)
		{
			/*Exits the game*/
			printf("You died!");
			return 0;
		}

		/*Condition where the PlayerMovement is 1(power up picked)*/
		else if (save == 2)
		{
			/*Adds 1 to the power up*/
			pickedPw++;
		}

		/*Condition where the game mode is not the parctice mode*/
		if (gamemode != '1')
		{
			
			/*EnemyShoot is only called if the EnemyLaser is 4*/
			if (EnemyLaser == 4)
			{
				EnemyShoot(Space, SPACE_HEIGHT, SPACE_WIDTH);

				/*Calls EnemyBullet and if it returns 1, one life will be substracted*/
				if (EnemyBullet(Space, SPACE_HEIGHT, SPACE_WIDTH, spaceship) == 1)
				{
					lifes--;

					/*Condition where the number of lifes is 0*/
					if (lifes == 0)
					{
						/*Exits the game*/
						printf("You died!");
						break;
					}
				}

				/*Sets EnemyLaser to 0*/
				EnemyLaser = 0;
			}
			/*Adds 1 to enemy laser*/
			EnemyLaser++;
		}

		/*Substracts one to freeze*/
		freeze--;
	}
    
	/*Returns 0*/
    return 0;
} 