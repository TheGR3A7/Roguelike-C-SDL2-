#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Standart values.h"
#include "func.h"

void InitializePlayer(Player* player, SDL_Renderer* ren, const char* texturePath, int x, int y) 
{

    player->texture = loadTextureFromFile(texturePath, &(player->position), ren);
    player->position.x = x;
    player->position.y = y;
    player->position.w = 125; 
    player->position.h = 150; 

    player->hp = 100; 
    player->damage = 35;
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