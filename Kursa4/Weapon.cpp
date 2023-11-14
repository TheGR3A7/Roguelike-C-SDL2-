#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Weapon.h"
#include "func.h"
#include "Player.h"
#include "Standart values.h"

void InitializeWeapons(Weapon weapons[], int numWeapons)
{
    weapons[0].name = "Knife";
    weapons[0].damage = 10;

    weapons[1].name = "Pistol";
    weapons[1].damage = 20;

    weapons[2].name = "Grenade";
    weapons[2].damage = 50;
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
            bullet.bullet_mas[i] = { 0, WINDOW_HEIGHT + bullet.size_y + 1, 0, 0 };
        }

        bullet.is_NULL = true;
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