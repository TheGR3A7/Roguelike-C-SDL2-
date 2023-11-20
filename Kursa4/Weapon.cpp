#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Weapon.h"
#include "func.h"
#include "Player.h"


void InitializeWeapons(Weapon weapons[], int numWeapons)
{
    weapons[0].name = "Knife";

    weapons[1].name = "Pistol";

    weapons[2].name = "Grenade";
}


void CreateBullet(Bullet& bullet, Player& player, SDL_Renderer* ren)
{
        if (bullet.texture == nullptr)
        {
            bullet.texture = loadTextureFromFile("BulletBlue.png", &bullet.rect, ren);
        }

        bullet.size_x = 16;
        bullet.size_y = 8;
        bullet.dmg = 20;
        bullet.cd = 500;
        bullet.vy = 500;
        bullet.vx = 500;
        bullet.count = MAX_BULLETS;

        for (int i = 0; i < bullet.count; i++)
        {
            bullet.bullet_mas[i] = { 0,(int) WINDOW_HEIGHT + bullet.size_y + 1, 0, 0 };
        }

        bullet.is_NULL = true;
}

void CreateEnemyBullet(Enemy_Bullet& enemybullet, Enemy enemy[], SDL_Renderer* ren)
{
    if (enemybullet.texture == nullptr)
    {
        enemybullet.texture = loadTextureFromFile("BulletRed.png", &enemybullet.rect, ren);
    }

    enemybullet.size_x = 16;
    enemybullet.size_y = 8;
    enemybullet.dmg = 20;
    enemybullet.cd = 1000;
    enemybullet.vy = 300;
    enemybullet.vx = 300;
    enemybullet.count = MAX_ENEMYBULLETS;

    for (int i = 0; i < enemybullet.count; i++)
    {
        enemybullet.bullet_mas[i] = { 0,(int)WINDOW_HEIGHT + enemybullet.size_y + 1, 0, 0 };
    }

    enemybullet.is_NULL = true;
}

bool CheckCooldown(Bullet& bullet, int dt)
{
    bullet.cur_time += dt;
    if (bullet.cur_time >= bullet.cd)
    {
        bullet.cur_time -= bullet.cd;
        return false;
    }
    return true;
}

void EnemyBulletDraw(Enemy_Bullet enemybullet, SDL_Renderer* ren)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    for (int i = 0; i < enemybullet.count; i++)
        if (enemybullet.active_bullet[i] == 1)
        {
            if (enemybullet.bulletDirection[i] == DIR_LEFT)
            {
                flip = SDL_FLIP_HORIZONTAL;
            }
            else
                flip = SDL_FLIP_NONE;
            SDL_RenderCopyEx(ren, enemybullet.texture, NULL, &enemybullet.bullet_mas[i], 0, NULL, flip);
        }
}

void BulletDraw(Bullet bullet, SDL_Renderer* ren)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    for (int i = 0; i < bullet.count; i++)
        if (bullet.active_bullet[i] == 1)
        {
            if (bullet.bulletDirection[i] == DIR_LEFT)
            {
                flip = SDL_FLIP_HORIZONTAL;
            }
            else
                flip = SDL_FLIP_NONE;
            SDL_RenderCopyEx(ren, bullet.texture, NULL, &bullet.bullet_mas[i], 0, NULL, flip);
        }
}

void CreateGrenade(Grenade& grenade, Player& player, SDL_Renderer* ren)
{
    if (grenade.texture == nullptr)
    {
        grenade.texture = loadTextureFromFile("grenade.png", &grenade.rect, ren);
    }

    grenade.size_x = 25;
    grenade.size_y = 25;
    grenade.dmg = 30;
    grenade.cd = 800;
    grenade.vy = 300;
    grenade.vx = 300;
    grenade.count = MAX_GRENADE;

    for (int i = 0; i < grenade.count; i++)
    {
        grenade.grenade_mas[i] = { 0,(int)WINDOW_HEIGHT + grenade.size_y + 1, 0, 0 };
        grenade.is_Moving[i] = true;
    }
    grenade.is_NULL = true;
}

bool CheckCooldownGrenade(Grenade& grenade, int dt)
{
    grenade.cur_time += dt;
    if (grenade.cur_time >= grenade.cd)
    {
        grenade.cur_time -= grenade.cd;
        return false;
    }
    return true;
}

void GrenadeDraw(Grenade grenade, SDL_Renderer* ren)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    for (int i = 0; i < grenade.count; i++)
        if (grenade.active_grenade[i] == 1)
        {
            if (grenade.grenadeDirection[i] == DIR_LEFT)
            {
                flip = SDL_FLIP_HORIZONTAL;
            }
            else
                flip = SDL_FLIP_NONE;
            SDL_RenderCopyEx(ren, grenade.texture, NULL, &grenade.grenade_mas[i], 0, NULL, flip);
        }
}