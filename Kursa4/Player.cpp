#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string.h>
#include "Player.h"
#include "Weapon.h"
#include "Map.h"


void InitializePlayer(Player* player, SDL_Renderer* ren, const char* texturePath, int x, int y) 
{

    player->texture = loadTextureFromFile(texturePath, &(player->position), ren);
    player->position.x = x;
    player->position.y = y;
    player->position.w = 81; 
    player->position.h = 100; 
    player->prevPosition = player->position;

    player->hp = 0; 
    player->money = 0;
    player->maxhp = 200;
    player->maxmoney = 999;

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


void CheckCollision(Player* player, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], SDL_Rect &tempPosition, Enemy enemy[])
{
    bool collision = false;

    // Проверка коллизий со всеми элементами препятствий
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            SDL_Rect obstacle = obstElements[i][j].position;

            if (obstElements[i][j].symbol != ' ' && SDL_HasIntersection(&tempPosition, &obstacle))
            {
                collision = true;
                break;
            }
        }
        if (collision)
        {
            break;
        }
    }

    // Проверка коллизий со всеми элементами препятствий
    for (int i = 0; i < 2; i++)
    {
            SDL_Rect enemies = enemy[i].position;

            if (SDL_HasIntersection(&tempPosition, &enemies))
            {
                collision = true;
                break;
            }
        if (collision)
        {
            break;
        }
    }


    // Если нет коллизий, обновите позицию игрока
    if (!collision)
    {
        player->position = tempPosition;
    }
}



void CheckLocation(Player& player, SDL_Renderer* ren, MapElement surfElements[MAP_HEIGHT][MAP_WIDTH], MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], int& currentLocation)
{
    if (currentLocation == 1)
    {
        if (player.position.y >= 200 && (player.position.x >= WINDOW_WIDTH - (player.position.w / 2)) && player.position.y <= 400)
        {
            currentLocation = 2;
            LoadMapDataFromFile("surfLoc2.txt", "obstLoc2.txt");
            LoadSurfaceElements(ren, surfElements);
            LoadObstacleElements(ren, obstElements);
            player.position.x = 50;
        }
    }
    else if (currentLocation == 2)
    {
        if (player.position.y >= 200 && (player.position.x <= 0 - (player.position.w / 2)) && player.position.y <= 400)
        {
            currentLocation = 1;
            LoadMapDataFromFile("surfLoc1.txt", "obstLoc1.txt");
            LoadSurfaceElements(ren, surfElements);
            LoadObstacleElements(ren, obstElements);
            player.position.x = 900;
        }
        else if (player.position.y >= 50  && (player.position.x >= WINDOW_WIDTH - (player.position.w / 2)) && player.position.y <= 500 )
        {
            currentLocation = 3;
            LoadMapDataFromFile("surfLoc3.txt", "obstLoc3.txt");
            LoadSurfaceElements(ren, surfElements);
            LoadObstacleElements(ren, obstElements);
            player.position.x = 50;
        }
    }
    else if (currentLocation == 3)
    {
        if (player.position.y >= 50  && (player.position.x <= 0 - (player.position.w / 2)) && player.position.y <= 500)
        {
            currentLocation = 2;
            LoadMapDataFromFile("surfLoc2.txt", "obstLoc2.txt");
            LoadSurfaceElements(ren, surfElements);
            LoadObstacleElements(ren, obstElements);
            player.position.x = 900;
        }
    }
}

void UpdatePlayer(Player* player, int isUpPressed, int isDownPressed, int isLeftPressed, int isRightPressed, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], Enemy* enemy)
{
    bool hasMovement = isUpPressed || isDownPressed || isLeftPressed || isRightPressed;

    if (hasMovement) 
    {
        SDL_Rect tempPosition = player->position;
        if (isUpPressed && !isDownPressed) tempPosition.y -= 5;
        if (!isUpPressed && isDownPressed) tempPosition.y += 5;
        if (isRightPressed && !isLeftPressed)
        {
            player->direction = DIR_RIGHT;
            tempPosition.x += 5;
        }
        if (!isRightPressed && isLeftPressed)
        {
            player->direction = DIR_LEFT;
            tempPosition.x -= 5;
        }
        CheckCollision(player, obstElements, tempPosition, enemy);
    }

    if (hasMovement) 
{
        int cur_time = SDL_GetTicks();
        int deltatime = cur_time - player->lastFrameTime;

        if (deltatime >= player->frameTime) {
            player->frame = (player->frame + 1) % player->frameCount;
            player->lastFrameTime = cur_time;
        }
    }
}

void BulletSpawn(Bullet& bullet, Player* player)
{

    for (int i = 0; i < 50; i++)
        if (bullet.bullet_mas[i].y > WINDOW_HEIGHT + bullet.size_y && bullet.active_bullet[i] == 1)
        {
            bullet.pos_x = player->position.x + player->position.w / 2 - 10;
            bullet.pos_y = player->position.y + player->position.h *2.8 /4;
            bullet.bullet_mas[i] = { (int)bullet.pos_x, (int)bullet.pos_y, bullet.size_x, bullet.size_y };
        }

}


void BulletMovement(Bullet& bullet, Player* player, int dt)
{
    int cnt = 0;
    for (int i = 0; i < bullet.count; i++)
    {
        if (bullet.active_bullet[i] == 0)
            cnt++;
    }
    if (cnt == bullet.count && !bullet.is_NULL)
        bullet.is_NULL = true;
    else
        bullet.is_NULL = false;
    if (!bullet.is_NULL)
    {
        for (int i = 0; i < bullet.count; i++)
        {
            if (bullet.active_bullet[i] == 0 && bullet.bullet_mas[i].y != WINDOW_HEIGHT + bullet.size_y + 1)
                bullet.bullet_mas[i] = { 0, WINDOW_HEIGHT + bullet.size_y + 1, 0, 0 };
            if (bullet.active_bullet[i] == 1)
            {
                if (bullet.bulletDirection[i] == DIR_LEFT)
                    bullet.bullet_mas[i].x -= bullet.vx * dt / 1000;
                else if (bullet.bulletDirection[i] == DIR_RIGHT)
                    bullet.bullet_mas[i].x += bullet.vx * dt / 1000;
                if (bullet.bullet_mas[i].y + bullet.size_y < 0)
                {
                    bullet.bullet_mas[i] = { 0, WINDOW_HEIGHT + bullet.size_y + 1, 0, 0 };
                    bullet.active_bullet[i] = 0;
                }
            }
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
    enemy->position.w = 81;
    enemy->position.h = 100;

    enemy->hp = 50;
    enemy->damage = 35;
    enemy->money = 50;

    enemy->frame = 0;
    enemy->count = 0;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
void InitializeBonus(Bonus* bonus, SDL_Renderer* ren, const char* texturePath, int x, int y)
{
    bonus->texture = loadTextureFromFile(texturePath, &(bonus->position), ren);
    bonus->position.x = x;
    bonus->position.y = y;
    bonus->position.w = 20;
    bonus->position.h = 20;
}

void RenderBonus(Bonus bonus, SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, bonus.texture, NULL, &(bonus.position));
}