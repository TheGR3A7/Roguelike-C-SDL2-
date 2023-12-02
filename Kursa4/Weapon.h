#pragma once
#include <SDL.h>
#include "func.h"
#include "Standart values.h"

const int MAX_BULLETS = 100;
const int MAX_ENEMYBULLETS = 100;
const int MAX_GRENADE = 50;

struct Player;
struct Enemy;

struct Weapon {
    const char* name;
    int damage;
};

struct Bullet {
    int size_x, size_y, dmg, cd, cur_time = 0, count;
    double pos_x, pos_y, vx;
    SDL_Rect bullet_mas[MAX_BULLETS];
    int bulletDirection[MAX_BULLETS];
    int active_bullet[MAX_BULLETS] = { 0 };
    SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Texture* texture = nullptr;
    bool is_NULL;
};

struct Explosion 
{
    SDL_Texture* texture;
    SDL_Rect rect;
    int frameCount;
    int frameTime;
    int curFrame;
    int lastFrameTime;
    bool isActive;
};

struct Grenade {
    int size_x, size_y, dmg, cd, cur_time = 0, count;
    double pos_x, pos_y, vx;
    SDL_Rect grenade_mas[MAX_GRENADE];
    int grenadeDirection[MAX_GRENADE];
    int active_grenade[MAX_GRENADE] = { 0 };
    SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Texture* texture = nullptr;
    int is_Moving[MAX_GRENADE];
    bool is_NULL;

    int damageInterval;     
    int lastDamageTime[MAX_GRENADE];
    Explosion explosion[MAX_GRENADE];
};

struct Enemy_Bullet
{
    int size_x, size_y, dmg, cd, cur_time = 0, count;
    double pos_x, pos_y, vx;
    SDL_Rect bullet_mas[MAX_ENEMYBULLETS];
    int bulletDirection[MAX_ENEMYBULLETS];
    int active_bullet[MAX_ENEMYBULLETS] = { 0 };
    SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Texture* texture = nullptr;
    bool is_NULL;
    int cur_frame_time = 0, max_frame_time = 200, frame = 0, max_frame = 4;
};


bool CheckCooldown(Bullet& bullet, int dt);
void CreateBullet(Bullet& bullet, Player& player, SDL_Renderer* ren);
void CreateEnemyBullet(Enemy_Bullet& enemybullet, Enemy enemy[], SDL_Renderer* ren);
void BulletDraw(Bullet bullet, SDL_Renderer* ren);
void CreateGrenade(Grenade& grenade, Player& player, SDL_Renderer* ren);
bool CheckCooldownGrenade(Grenade& grenade, int dt);
void GrenadeDraw(Grenade grenade, SDL_Renderer* ren);

void InitializeExplosion(Explosion& explosion, SDL_Renderer* ren);
void Explode(Explosion& explosion, int x, int y, SDL_Renderer* ren);
void UpdateExplosion(Explosion& explosion);
void ExplosionDraw(Explosion& explosion, SDL_Renderer* ren);



