#pragma once
#include <SDL.h>
#include <string.h>
#include "Weapon.h"
#include "Map.h"


struct Player
{
	SDL_Texture* texture;
	SDL_Rect position;
	SDL_Rect prevPosition;
	int hp;
	int maxhp;
	int money;
	int maxmoney;
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
	int money;
	int count;
	int frameCount;
	int frameTime;
	int lastFrameTime;
	int direction;
};

struct Bonus
{
//	BonusType Bontype;
	SDL_Texture* texture;
	SDL_Rect position;
};

enum BonusType
{
	Heart,
	Money
};

void InitializePlayer(Player* player, SDL_Renderer* ren, const char* texturePath, int x, int y);
void RenderPlayer(Player* player, SDL_Renderer* ren);
void CheckCollision(Player* player, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], SDL_Rect& tempPosition, Enemy enemy[]);
void CheckLocation(Player& player, SDL_Renderer* ren, MapElement surfElements[MAP_HEIGHT][MAP_WIDTH], MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], int& currentLocation);
void UpdatePlayer(Player* player, int isUpPressed, int isDownPressed, int isLeftPressed, int isRightPressed, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], Enemy* enemy);
void BulletSpawn(Bullet& bullet, Player* player);
void BulletMovement(Bullet& bullet, Player* player, int dt);
void CleanUpPlayer(Player* player);
void InitializeEnemy(Enemy* enemy, SDL_Renderer* ren, const char* texturePath, int x, int y);
void RenderEnemy(Enemy* enemy, SDL_Renderer* ren);
void UpdateEnemy(Enemy* enemy);
void InitializeBonus(Bonus* bonus, SDL_Renderer* ren, const char* texturePath, int x, int y);
void RenderBonus(Bonus bonus, SDL_Renderer* ren);
void CollisionBulletWithObstacle(Bullet* bullet, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], SDL_Rect& tempPosition);