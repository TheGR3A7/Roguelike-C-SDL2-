#pragma once

#include <SDL.h>
#include "func.h"
#include "Standart values.h"

struct Player
{
	SDL_Texture* texture;
	SDL_Rect position;
	int hp;
	int damage;
	int money;
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