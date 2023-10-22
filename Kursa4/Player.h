#pragma once

#include <SDL.h>
#include <string.h>
#include "Weapon.h"

struct Player
{
	SDL_Texture* texture;
	SDL_Rect position;
	int hp;
	int money;
	int frame;     
	int frameCount;
	int frameTime;  
	int lastFrameTime;
	int direction;
	Weapon currentWeapon;
};

enum EnemyType 
{
	Tuco,
	Hector
};

struct Enemy 
{
	EnemyType type;
	SDL_Texture* texture;
	SDL_Rect position;
	int hp;
	int damage;
	int frame;
	int frameCount;
	int frameTime;
	int lastFrameTime;
	int direction;
};

void InitializePlayer(Player* player, SDL_Renderer* ren, const char* texturePath, int x, int y);
void RenderPlayer(Player* player, SDL_Renderer* ren);
void UpdatePlayer(Player* player, int isUpPressed, int isDownPressed, int isLeftPressed, int isRightPressed);
void CleanUpPlayer(Player* player);
void InitializeEnemy(Enemy* enemy, SDL_Renderer* ren, const char* texturePath, int x, int y);
void RenderEnemy(Enemy* enemy, SDL_Renderer* ren);
void UpdateEnemy(Enemy* enemy);
bool IsKnifeHit(Player* player, Enemy* enemy);
void Shoot(Player* player, Enemy* enemy);