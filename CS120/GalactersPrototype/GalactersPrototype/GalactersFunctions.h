#ifndef GALACTERSFUNCTIONS_H
#define GALACTERSFUNCTIONS_H

void CreateSpace(char (*Space)[SPACE_HEIGHT], int heigth, int width, int content);
void AddPlayer(char (*Space)[SPACE_HEIGHT],int posX, int posY,int spaceship);
int AddEnemy(char(*Space)[SPACE_HEIGHT], int width);
int AddAllEnemies(char(*Space)[SPACE_HEIGHT], int width);
void AddPowerUP(char(*Space)[SPACE_HEIGHT], int posY, int powerup);
void AddShields(char(*Space)[SPACE_HEIGHT], int height, int width);
void PrintSpace(char (*Space)[SPACE_HEIGHT], int heigth, int width);
int PlayerMovement(char(*Space)[SPACE_HEIGHT], int heigth, int width, int spaceship);
int Bullet(char(*Space)[SPACE_HEIGHT], int heigth, int width, int *enemies);
int EnemyMovement(char(*Space)[SPACE_HEIGHT], int heigth, int width,int *direction,int *down);
void EnemyShoot(char(*Space)[SPACE_HEIGHT], int heigth, int width);
int EnemyBullet(char(*Space)[SPACE_HEIGHT], int heigth, int width, int spaceship);
int CheckDirection(char(*Space)[SPACE_HEIGHT], int heigth);

#endif
