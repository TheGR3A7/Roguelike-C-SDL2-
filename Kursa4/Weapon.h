#pragma once
#include <SDL.h>
#include "func.h"
#include "Standart values.h"

const int MAX_BULLETS = 50;

struct Player;

struct Weapon {
    const char* name;
    int damage;
};

struct Bullet {
    int size_x, size_y, dmg, cd, cur_time = 0, count;
    double pos_x, pos_y, vx, vy;
    SDL_Rect bullet_mas[50];
    int bulletDirection[MAX_BULLETS];
    int active_bullet[50] = { 0 };
    SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Texture* texture = nullptr;
    bool is_NULL;
};

struct Enemy_Bullet
{
    int size_x, size_y, dmg, count;
    double pos_x, pos_y, speed;
    SDL_Rect bullet_mas[100];
    int bulletDirection[MAX_BULLETS];
    int active_bullet[100] = { 0 };
    SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Texture* texture;
    bool is_NULL;
    int cur_frame_time = 0, max_frame_time = 200, frame = 0, max_frame = 4;
};

bool CheckCooldown(Bullet& bullet, int dt);
void CreateBullet(Bullet& bullet, Player& player, SDL_Renderer* ren);
void BulletDraw(Bullet bullet, SDL_Renderer* ren);
