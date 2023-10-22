#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string.h>
#include "Player.h"
#include "Weapon.h"

void InitializePlayer(Player* player, SDL_Renderer* ren, const char* texturePath, int x, int y) 
{

    player->texture = loadTextureFromFile(texturePath, &(player->position), ren);
    player->position.x = x;
    player->position.y = y;
    player->position.w = 125; 
    player->position.h = 150; 

    player->hp = 100; 
    player->money = 0;

    player->frame = 0;
    player->frameCount = 4; 
    player->frameTime = 200; 
    player->lastFrameTime = 0; 
    player->direction = DIR_RIGHT;
}

void RenderPlayer(Player* player, SDL_Renderer* ren)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (player->direction == DIR_LEFT)
    {
        flip = SDL_FLIP_HORIZONTAL; 
    }

    SDL_Rect srcRect = { player->frame * player->position.w, 0,  player->position.w,  player->position.h };
    SDL_RenderCopyEx(ren, player->texture, &srcRect, &(player->position), 0, NULL, flip);
}

void UpdatePlayer(Player* player, int isUpPressed, int isDownPressed, int isLeftPressed, int isRightPressed)
{
    if (isUpPressed && !isDownPressed) player->position.y -= 5;
    if (!isUpPressed && isDownPressed) player->position.y += 5;
    if (isRightPressed && !isLeftPressed) player->position.x += 5;
    if (!isRightPressed && isLeftPressed) player->position.x -= 5;

    bool hasMovement = isUpPressed || isDownPressed || isLeftPressed || isRightPressed;

    if (hasMovement)
    {
        int cur_time = SDL_GetTicks();
        int deltatime = cur_time - player->lastFrameTime;

        if (deltatime >= player->frameTime)
        {
            player->frame = (player->frame + 1) % player->frameCount;
            player->lastFrameTime = cur_time;
        }
    }
}

void CleanUpPlayer(Player* player) 
{
    if (player->texture)
        SDL_DestroyTexture(player->texture);
}


///////////////////////////////////////////////////////////////////////////////////////////////


void InitializeEnemy(Enemy* enemy, SDL_Renderer* ren, const char* texturePath, int x, int y) 
{
    enemy->texture = loadTextureFromFile(texturePath, &(enemy->position), ren);
    enemy->position.x = x;
    enemy->position.y = y;
    enemy->position.w = 125;
    enemy->position.h = 150;

    enemy->hp = 50;
    enemy->damage = 35;

    enemy->frame = 0;
    enemy->frameCount = 4;
    enemy->frameTime = 200;
    enemy->lastFrameTime = 0;
    enemy->direction = DIR_RIGHT;
}

void RenderEnemy(Enemy* enemy, SDL_Renderer* ren) 
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (enemy->direction == DIR_LEFT)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_Rect srcRect = { enemy->frame * enemy->position.w, 0,  enemy->position.w,  enemy->position.h };
    SDL_RenderCopyEx(ren, enemy->texture, &srcRect, &(enemy->position), 0, NULL, flip);
}

void UpdateEnemy(Enemy* enemy) 
{
    if (enemy->type == Tuco) {
        // Обработка действий для Tuco (стрельба с пистолета)
        // Например, проверьте, если Tuco в поле видимости игрока, и, если да, пусть он стреляет.
        if (enemy->hp <= 0) {
            SDL_DestroyTexture(enemy->texture);
            enemy->texture = NULL;
        }
    }
    else if (enemy->type == Hector) {
        // Обработка действий для Hector (подбегание и взрыв)
        // Например, пусть Hector приближается к игроку и взрывается, если близко.
        if (enemy->hp <= 0) {
            SDL_DestroyTexture(enemy->texture);
            enemy->texture = NULL;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool IsKnifeHit(Player* player, Enemy* enemy) 
{
    float distance = sqrt(pow(player->position.x - enemy->position.x, 2) + pow(player->position.y - enemy->position.y, 2));

    return distance <= KNIFE_ATTACK_RADIUS;
}


void Shoot(Player* player, Enemy* enemy)
{
    if (strcmp(player->currentWeapon.name, "Knife") == 0)
    {
        if (IsKnifeHit(player, enemy)) 
        {
            enemy->hp -= player->currentWeapon.damage;
        }
    }
    else if (strcmp(player->currentWeapon.name, "Pistol") == 0)
    {
        // Обработайте выстрел с пистолетом
        // Напишите код для выстрела с пистолетом
    }
    else if (strcmp(player->currentWeapon.name, "Grenade") == 0) {
        // Обработайте бросок гранаты
        // Напишите код для броска гранаты
    }
}

