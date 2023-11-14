#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "func.h"
#include "Player.h"


void About(SDL_Renderer* ren);
void Menu(SDL_Renderer* ren);
bool PointInRect(int x, int y, const SDL_Rect& rect);
void CollisionWithBullet(Player& player, Bullet& bullet, Enemy enemy[], Bonus bonus[], SDL_Renderer* ren);
void CollisionWithBonus(Player& player, Bonus bonus[]);
void RenderGameText(TTF_Font* font, Player* player, SDL_Renderer* ren);
void DeadWallpaper(Player* player, SDL_Renderer* ren);
void Game(SDL_Renderer* ren);

