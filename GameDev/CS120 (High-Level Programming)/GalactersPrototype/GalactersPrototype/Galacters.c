/******************************************************************************
filename    galacters.c
author      Gentzane Pastor
DP email    gentzane.pastor@digipen.edu
course      CS120  
project     final       
due date    04/29/2018

Brief Description: 
A game inspired on Space Invaders.
******************************************************************************/
#include <stdio.h>  /*printf, scanf*/
#include <time.h> /*time*/
#include <stdlib.h>/*srand,rand*/
#include "GalactersDefines.h" 
#include "GalactersFunctions.h" 
/******************************************************************************
Function: CreateSpace.

Description: Creates the Space for the game.

Inputs: Space[SPACE_HEIGHT][SPACE_WIDTH], heigth, width, content.
******************************************************************************/
void CreateSpace(char (*Space)[SPACE_HEIGHT],int heigth, int width, int content)
{
	int i, j;

	//Sets the whole array to spaces
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < heigth; j++)
		{
			Space[i][j] = content;
		}
	}
}
/******************************************************************************
Function: AddPlayer.

Description: Adds the player to the screen.

Inputs: (*Space)[SPACE_HEIGHT], posX, posY, spaceship.
******************************************************************************/
void AddPlayer(char (*Space)[SPACE_HEIGHT], int posX, int posY,int spaceship)
{
    Space[posX][posY-1]= spaceship;
}
/******************************************************************************
Function: AddPowerUP.

Description: Adds the power up to the screen.

Inputs: (*Space)[SPACE_HEIGHT], posY, powerup.
******************************************************************************/
void AddPowerUP(char(*Space)[SPACE_HEIGHT], int posY,int powerup)
{
	/*Sets a random position for the widht*/
	int x = rand() % 24;
	/*Seeds the rand number*/
	srand(time(0));

	/*Places the power up if the position is a white space*/
	if (Space[x][posY - 1] == WHITE_SPACE)
	{
		Space[x][posY - 1] = powerup;
	}
}
/******************************************************************************
Function: AddShields.

Description: Adds the player shields to the screen.

Inputs: (*Space)[SPACE_HEIGHT], heigth, width.
******************************************************************************/
void AddShields(char(*Space)[SPACE_HEIGHT], int height, int width)
{
	int x=0;

	int y = height - 5;

	Space[x + 2][y] = '7';
	Space[x + 3][y] = '7';
	Space[x + 4][y] = '7';

	Space[x + 8][y] = '7';
	Space[x + 9][y] = '7';
	Space[x + 10][y] = '7';

	Space[x + 14][y] = '7';
	Space[x + 15][y] = '7';
	Space[x + 16][y] = '7';

	Space[x + 20][y] = '7';
	Space[x + 21][y] = '7';
	Space[x + 22][y] = '7';
	

}
/******************************************************************************
Function: AddEnemy.

Description: Adds the enemies to the screen.

Inputs: Space[SPACE_HEIGHT][SPACE_WIDTH], width.
******************************************************************************/
int  AddEnemy(char(*Space)[SPACE_HEIGHT], int width)
{
	int i, j;
	int enemies = 0;

	//Adds the enemies in 10 rows
	for (i = 4; i < width - 4; i++)
	{
		for (j = 1; j < 11; j++)
		{
			Space[i][j] = ALIEN;
			enemies++;
		}
	}

	return enemies;
}
/******************************************************************************
Function: AddAllEnemies.

Description: Adds both types of enemies to the screen.

Inputs: Space[SPACE_HEIGHT][SPACE_WIDTH], width.
******************************************************************************/
int AddAllEnemies(char(*Space)[SPACE_HEIGHT], int width)
{
	int i, j;
	int enemies = 0;

	/*Adds the enemies in 10 rows(the first 5 rows normal enemies 
	and the others super enemies)*/
	for (i = 4; i < width - 4; i++)
	{
		for (j = 1; j < 11; j++)
		{
			if (j > 5)
			{
				Space[i][j] = SUPERALIEN;
				enemies++;
			}
			else
			{
				Space[i][j] = ALIEN;
				enemies++;
			}

		}
	}
	return enemies;
}
/******************************************************************************
Function: EnemyMovement.

Description: Makes the enemies move.

Inputs: Space[SPACE_HEIGHT][SPACE_WIDTH],heigth, width, *direction, *down.
******************************************************************************/
int EnemyMovement(char(*Space)[SPACE_HEIGHT], int heigth, int width, int *direction,int *down)
{
	int i, j;
	int x, y;

	int checkDown = 0;

		//Sets a direction depending on the value returned in CheckDirection (right)
		if (CheckDirection(Space, heigth) == 1)
		{
			*direction = 1;
			*down = 1;
			checkDown = 1;
		}
		//Sets a direction depending on the value returned in CheckDirection (left)
		else if (CheckDirection(Space, heigth) == 2)
		{
			*direction = 0;
			*down = 1;
			checkDown = 1;
		}

		//If the direction is 0 moves left
		if (*direction == 0)
		{
			for (i = 0; i < width; i++)
			{
				for (j = heigth; j >= 0; j--)
				{
					x = i;
					y = j;

					//Moves left
					if (((Space[x][y] == ALIEN) || (Space[x][y] == SUPERALIEN)) && (*down == 0))
					{

						if (Space[x][y] == ALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							x += GOING_LEFT;
							Space[x][y] = ALIEN;
						}
						else if (Space[x][y] == SUPERALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							x += GOING_LEFT;
							Space[x][y] = SUPERALIEN;
						}
					}
					//If down is 1 it will also move down
					else if (((Space[x][y] == ALIEN) || (Space[x][y] == SUPERALIEN)) && (*down == 1))
					{

						if (Space[x][y] == ALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							y++;
							x += GOING_LEFT;
							Space[x][y] = ALIEN;
						}
						else if (Space[x][y] == SUPERALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							y++;
							x += GOING_LEFT;
							Space[x][y] = SUPERALIEN;
						}

						checkDown = 0;
					}
				}
			}

			if (checkDown == 0)
				*down = 0;
		}

		//If the direction is 1 moves right
		if (*direction == 1)
		{

			for (i = width - 1; i >= 0; i--)
			{
				for (j = heigth - 1; j >= 0; j--)
				{
					x = i;
					y = j;

					//Moves right
					if (((Space[x][y] == ALIEN) || (Space[x][y] == SUPERALIEN)) && (*down == 0))
					{


						if (Space[x][y] == ALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							x += GOING_RIGHT;
							Space[x][y] = ALIEN;
						}
						else if (Space[x][y] == SUPERALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							x += GOING_RIGHT;
							Space[x][y] = SUPERALIEN;
						}
					}

					//If down is 1 it will also move down
					else if (((Space[x][y] == ALIEN) || (Space[x][y] == SUPERALIEN)) && (*down == 1))
					{
						if (Space[x][y] == ALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							y++;
							x += GOING_RIGHT;
							Space[x][y] = ALIEN;
						}
						else if (Space[x][y] == SUPERALIEN)
						{
							Space[x][y] = WHITE_SPACE;
							y++;
							x += GOING_RIGHT;
							Space[x][y] = SUPERALIEN;
						}


						checkDown = 0;
					}
				}
			}

			//Checks if down is false to stop moving the enemies down
			if (checkDown == 0)
				*down = 0;
		}
}
/******************************************************************************
Function: Direction.

Description: Checks the direction of the enemies.

Inputs: Space[SPACE_HEIGHT][SPACE_WIDTH],heigth.
******************************************************************************/
int CheckDirection(char(*Space)[SPACE_HEIGHT], int heigth)
{
	//Goes through all the rows
	for (int j = 0; j < heigth; j++)
	{
		//If an alien touches the left wall the direction will change
		if (((Space[LEFT_WALL][j] == ALIEN)||((Space[LEFT_WALL][j] == SUPERALIEN))))
		{
			return 1;
		}
		//If an alien touches the right wall the direction will change
		else if ((Space[RIGHT_WALL - 1][j] == ALIEN)||((Space[RIGHT_WALL - 1][j] == SUPERALIEN)))
		{
			return 2;
		}
	}

	return 0;
}
/******************************************************************************
Function: EnemyShoot.

Description: Makes the enemy shoot.

Inputs: (*Space)[SPACE_HEIGHT], heigth, width.
******************************************************************************/
void EnemyShoot(char(*Space)[SPACE_HEIGHT], int heigth, int width)
{
	int i, j;
	int x, y;
	int number = 0;

	srand(time(0));

	//Searches for the last aliens in the array 
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < heigth; j++)
		{
			y = j;
			x = rand()%18;

			//Makes a random alien shoot 
			if (((Space[x][y] == ALIEN) || (Space[x][y] == SUPERALIEN)) &&(Space[x][y+1] == WHITE_SPACE)&&(number%11==0))
			{
				Space[x][y+1] = ALIEN_BULLET;
			}
				
		}

		number++;
	}
	
}
/******************************************************************************
Function: EnemyBullet.

Description: Makes the enemy bullet move.

Inputs: (*Space)[SPACE_HEIGHT], heigth, width, spaceship.

Output: 1.
******************************************************************************/
int EnemyBullet(char(*Space)[SPACE_HEIGHT], int heigth, int width,int spaceship)
{
	int i, j;
	int x, y;
	int number = 3;
	int lifes = 3;

	/*Loop where number must be bigger than 0*/
	while (number > 0)
	{
		//Searches for the bullet of the alien in the array
		for (i = width - 1; i >= 0; i--)
		{
			for (j = heigth - 1; j >= 0; j--)
			{
				//When the bullet is found, saves the position
				if (Space[i][j] == ALIEN_BULLET)
				{
					x = i;
					y = j;

					//The bullet will continue moving if a space is in its next position
					if ((Space[x][y + 1] == WHITE_SPACE))
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = ALIEN_BULLET;
					}

					//If the alien bullet touches a player bullet, both will disapear
					if (Space[x][y + 1] == BULLET)
					{
						Space[x][y] = WHITE_SPACE;

					}

					/*Condition where an alien bullet touches a power up*/
					if (Space[x][y - 1] == FREEZY_PU)
					{
						/*The bullet will disapear*/
						Space[x][y] = WHITE_SPACE;
					}

					/*Conditions to decrement the player shield if an enemy bullet 
					touches them*/
					if (Space[x][y + 1] == '7')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = '6';
					}
					else if (Space[x][y + 1] == '6')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = '5';
					}
					else if (Space[x][y + 1] == '5')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = '4';
					}
					else if (Space[x][y + 1] == '4')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = '3';
					}
					else if (Space[x][y + 1] == '3')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = '2';
					}
					else if (Space[x][y + 1] == '2')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = '1';
					}
					else if (Space[x][y + 1] == '1')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y + 1] = WHITE_SPACE;
					}
				

					//If the bullet reaches the first row of the array, it will disapear
					if (y+1 == heigth)
					{
						Space[x][y + 1] = WHITE_SPACE;
					}
					/*If a bullet touches the player, you will lose and the player will
					return to its first position*/
					if (Space[x][y + 1] == spaceship)
					{
						lifes--;
						AddPlayer(Space, SPACESHIP_X, SPACESHIP_Y, spaceship);
						Space[x][y + 1] = WHITE_SPACE;
						return 1;

						/*Condition where the number of lifes is 0*/
						if (lifes == 0)
						{
							/*Replaces the player with a white space and returns 1*/
							Space[x][y + 1] = WHITE_SPACE;
							return 1;
						}
					}
				}
			}
		}
		/*Sustracts 1 to number*/
		number--;
	}

}
/******************************************************************************
Function: PlayerMovement.

Description: Makes the player move left(A), rigth(D) and shoot(g).

Inputs: (*Space)[SPACE_HEIGHT], heigth, width.

Output: 0,1,2.
******************************************************************************/
int PlayerMovement(char (*Space)[SPACE_HEIGHT],int heigth, int width, int spaceship)
{
	int i, j;
    int x=0;
    int y=0;
    char key=0;


	//Searches for the player in the array and saves its position
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < heigth; j++)
		{
			if(Space[i][j]== spaceship)
            {
                y=j;
                x=i;
            }
		}
	}
    
	//Gets the input for the player
	key=getch();
    
	//Replaces the player by a white space
    for (i = 0; i < width; i++)
	{
		for (j = 0; j < heigth; j++)
		{
			if(Space[i][j]== spaceship)
            {
                Space[i][j]=WHITE_SPACE;
            }
		}
	}

	/*If the key pressed(the input) is A it will move 1 or 2 left
	(in case you have the speedy spaceship)*/
    if((key=='a')&&(x>0))
    {
		if(spaceship!= SPEEDY_SPACESHIP)
			 x--;
		else if ((spaceship == SPEEDY_SPACESHIP)&&(x+1>0))
		{
			x -= 2;
		}

    }
    
	/*If the key pressed(the input) is D it will move 1 or 2 right
	(in case you have the speedy spaceship)*/
    else if((key=='d')&&(x<width-1))
    {
		if (spaceship != SPEEDY_SPACESHIP)
			x++;

		else if ((spaceship == SPEEDY_SPACESHIP) && ((x + 1)>0))
		{
			x += 2;
		}
    }
   
	//If the key pressed(the input) is G it will shoot
	else if (key == 'g')
	{
		Space[x][y - 1] = BULLET;
		
	}
		
	/*Condition where an enemy touches the player*/
	if ((Space[x][heigth - 2] == ALIEN)||(Space[x][heigth -2] == SUPERALIEN))
	{
		/*Replaces the player with a white space and returns 1*/
		Space[x][y] = WHITE_SPACE;
		return 1;
	}

	/*Condition where the player finds a power up*/
	if ((Space[x][y] == FREEZY_PU))
	{
		/*Replaces the power up with a white space and returns 2*/
		Space[x][y] = spaceship;
		return 2;
	}

	/*Places the player*/
	Space[x][y] = spaceship;

    return 0;
}
/******************************************************************************
Function: Bullet.

Description: Makes the player bullet go up.

Inputs: (*Space)[SPACE_HEIGHT], heigth, width,*enemies.

Output:1,2,3.
******************************************************************************/
int Bullet(char(*Space)[SPACE_HEIGHT], int heigth, int width, int *enemies)
{
	int i, j;
	int x, y;
	int number = 2;

	/*Loop where number is bigger than 2*/
	while (number > 0)
	{
		//Searches for the bullet on the array
		for (i = 0; i < width; i++)
		{
			for (j = 0; j < heigth; j++)
			{
				//When the bullet is found, saves the position
				if (Space[i][j] == BULLET)
				{
					x = i;
					y = j;

					//The bullet will continue moving if a space is in its next position
					if (Space[x][y - 1] == WHITE_SPACE)
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = BULLET;
					}

					//If the bullet reaches the first row of the array, it will disapear
					if (y - 1 == 0)
					{
						Space[x][y - 1] = WHITE_SPACE;
					}

					/*Conditions to decrement the player shield if an enemy bullet
					touches them*/
					if (Space[x][y -1] == '7')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = '6';
					}
					else if (Space[x][y - 1] == '6')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = '5';
					}
					else if (Space[x][y - 1] == '5')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = '4';
					}
					else if (Space[x][y - 1] == '4')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = '3';
					}
					else if (Space[x][y - 1] == '3')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = '2';
					}
					else if (Space[x][y - 1] == '2')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = '1';
					}
					else if (Space[x][y - 1] == '1')
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = WHITE_SPACE;
					}

					/*Condition where a bullet touches a super alien*/
					if (Space[x][y - 1] == SUPERALIEN)
					{
						/*The super alien will be replaced by an normal alien 
						and it will return 2*/
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = ALIEN;

						return 2;
					}

					//If a bullet touches an alien, the alien will disapear
					else if (Space[x][y - 1] == ALIEN)
					{
						Space[x][y] = WHITE_SPACE;
						Space[x][y - 1] = WHITE_SPACE;
						(*enemies)--;

						//If the number of enemies is 0 you will win
						if (*enemies == 0)
						{
							return 1;
						}

						/*Returns 3 to add the score of a death enemy*/
						return 3;
					}

				}
			}
		}
		/*Substracts 1 to number*/
		number--;
	}
}
/******************************************************************************
Function: PrintSpace.

Description: Prints the limits of the space on the screen.

Inputs: (*Space)[SPACE_HEIGHT], heigth, width.
******************************************************************************/
void PrintSpace(char(*Space)[SPACE_HEIGHT], int heigth, int width)
{
    int i,j;
    
    for(i=0;i<(width+2);i++)
    {
        printf("__");
    }
    
    printf("\n");
    
    for(j=0;j<heigth;j++)
    {
        printf("| ");
        
        for(i=0;i<width;i++)
        {
            printf("%c ",Space[i][j]);
        }
        
        printf(" |\n");
    }
    for(i=0;i<(width+2);i++)
    {
        printf("__");
    }
    
    printf("\n");
}
