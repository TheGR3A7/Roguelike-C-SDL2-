#pragma once
#include <SDL.h>
#include <string.h>
#include "Weapon.h"
#include "Map.h"

const int MAX_ENEMY = 5;
const int MAX_BONUS = 10;

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

enum BonusType
{
	Heart,
	Money
};

struct Bonus
{
	BonusType Bontype;
	SDL_Texture* texture;
	SDL_Rect position;
	bool isActive;
};


void InitializePlayer(Player* player, SDL_Renderer* ren, const char* texturePath, int x, int y);
void RenderPlayer(Player* player, SDL_Renderer* ren);
void CheckCollision(Player* player, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], SDL_Rect& tempPosition, Enemy enemy[]);
void CheckLocation(Player& player, Enemy* enemy, Bonus bonus[MAX_BONUS], SDL_Renderer* ren, MapElement surfElements[MAP_HEIGHT][MAP_WIDTH], MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], int& currentLocation);
void UpdatePlayer(Player* player, int isUpPressed, int isDownPressed, int isLeftPressed, int isRightPressed, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], Enemy* enemy);
void BulletSpawn(Bullet& bullet, Player* player);
void BulletMovement(Bullet& bullet, Player* player, int dt);
void CleanUpPlayer(Player* player);
void InitializeEnemy(Enemy* enemies, Player* player, SDL_Renderer* ren, const char* hectorTexturePath, const char* tucoTexturePath, int x, int y, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH]);
void RenderEnemy(Enemy* enemy, SDL_Renderer* ren);
void RespawnEnemies(Enemy* enemies, Player* player, SDL_Renderer* ren, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH]);
void UpdateEnemy(Enemy* enemy);
void InitializeBonus(Bonus* bonus, SDL_Renderer* ren, const char* texturePath, int x, int y);
void RenderBonus(Bonus bonus, SDL_Renderer* ren);
void GrenadeSpawn(Grenade& grenade, Player* player);
void GrenadeMovement(Grenade& grenade, Player* player, int dt);
void CheckBulletCollisionWithObstacle(Bullet& bullet, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH]);
void CheckGrenadeCollisionWithObstacle(Grenade& grenade, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH]);
bool IsOverlap(int x1, int y1, int x2, int y2, int margin);
bool IsOverlapWithOtherEnemies(Enemy* enemies, int currentEnemyIndex, int margin);
bool IsOverlapWithObstacles(int x, int y, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH]);