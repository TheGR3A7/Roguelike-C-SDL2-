#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <random>
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

    player->hp = 100; 
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
    for (int i = 0; i < MAX_ENEMY; i++)
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



void CheckLocation(Player& player, Enemy* enemy, Bonus bonus[MAX_BONUS], SDL_Renderer* ren, MapElement surfElements[MAP_HEIGHT][MAP_WIDTH], MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], int& currentLocation)
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
            RespawnEnemies(enemy, &player, ren, obstElements);
            for (int i = 0; i < MAX_BONUS; i++)
            {
                bonus[i].position.x = 0;
                bonus[i].position.y = WINDOW_HEIGHT + 1;
            }
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
            RespawnEnemies(enemy, &player, ren, obstElements);
            for (int i = 0; i < MAX_BONUS; i++)
            {
                bonus[i].position.x = 0;
                bonus[i].position.y = WINDOW_HEIGHT + 1;
            }
        }
        else if (player.position.y >= 50  && (player.position.x >= WINDOW_WIDTH - (player.position.w / 2)) && player.position.y <= 500 )
        {
            currentLocation = 3;
            LoadMapDataFromFile("surfLoc3.txt", "obstLoc3.txt");
            LoadSurfaceElements(ren, surfElements);
            LoadObstacleElements(ren, obstElements);
            player.position.x = 50;
            RespawnEnemies(enemy, &player, ren, obstElements);
            for (int i = 0; i < MAX_BONUS; i++)
            {
                bonus[i].position.x = 0;
                bonus[i].position.y = WINDOW_HEIGHT + 1;
            }
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
            RespawnEnemies(enemy, &player, ren, obstElements);
            for (int i = 0; i < MAX_BONUS; i++)
            {
                bonus[i].position.x = 0;
                bonus[i].position.y = WINDOW_HEIGHT + 1;
            }
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

    for (int i = 0; i < MAX_BULLETS; i++)
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
                bullet.bullet_mas[i] = { 0, (int)WINDOW_HEIGHT + bullet.size_y + 1, 0, 0 };
            if (bullet.active_bullet[i] == 1)
            {
                if (bullet.bulletDirection[i] == DIR_LEFT)
                    bullet.bullet_mas[i].x -= bullet.vx * dt / 1000;
                else if (bullet.bulletDirection[i] == DIR_RIGHT)
                    bullet.bullet_mas[i].x += bullet.vx * dt / 1000;
                if (bullet.bullet_mas[i].y + bullet.size_y < 0)
                {
                    bullet.bullet_mas[i] = { 0, (int)WINDOW_HEIGHT + bullet.size_y + 1, 0, 0 };
                    bullet.active_bullet[i] = 0;
                }
            }
        }
    }
}

void GrenadeSpawn(Grenade& grenade, Player* player)
{

    for (int i = 0; i < MAX_GRENADE; i++)
        if (grenade.grenade_mas[i].y > WINDOW_HEIGHT + grenade.size_y && grenade.active_grenade[i] == 1)
        {
            grenade.pos_x = player->position.x + player->position.w / 2 - 10;
            grenade.pos_y = player->position.y + player->position.h * 2.8 / 4;
            grenade.grenade_mas[i] = { (int)grenade.pos_x, (int)grenade.pos_y, grenade.size_x, grenade.size_y };
        }

}


void GrenadeMovement(Grenade& grenade, Player* player, int dt)
{
    int cnt = 0;
    for (int i = 0; i < grenade.count; i++)
    {
        if (grenade.active_grenade[i] == 0)
            cnt++;
    }
    if (cnt == grenade.count && !grenade.is_NULL)
        grenade.is_NULL = true;
    else
        grenade.is_NULL = false;
    if (!grenade.is_NULL)
    {
        for (int i = 0; i < grenade.count; i++)
        {
            if (grenade.active_grenade[i] == 0 && grenade.grenade_mas[i].y != WINDOW_HEIGHT + grenade.size_y + 1)
                grenade.grenade_mas[i] = { 0, (int)WINDOW_HEIGHT + grenade.size_y + 1, 0, 0 };
            if (grenade.active_grenade[i] == 1)
            {
                if (grenade.is_Moving[i])
                {
                    if (grenade.grenadeDirection[i] == DIR_LEFT)
                        grenade.grenade_mas[i].x -= grenade.vx * dt / 1000;
                    else if (grenade.grenadeDirection[i] == DIR_RIGHT)
                        grenade.grenade_mas[i].x += grenade.vx * dt / 1000; 
                    if (abs(grenade.grenade_mas[i].x - player->position.x) >= 250)
                    {
                        grenade.is_Moving[i] = false;  
                    }
                }
                if (grenade.grenade_mas[i].y + grenade.size_y < 0)
                {
                    grenade.grenade_mas[i] = { 0, (int)WINDOW_HEIGHT + grenade.size_y + 1, 0, 0 };
                    grenade.active_grenade[i] = 0;
                }
            }
        }
    }
}


void CheckBulletCollisionWithObstacle(Bullet& bullet, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH])
{
    for (int k = 0; k < bullet.count; k++)
    {
        if (bullet.active_bullet[k])
        {
            SDL_Rect bulletRect = bullet.bullet_mas[k];

            // Проверка коллизий с препятствиями
            for (int i = 0; i < MAP_HEIGHT; i++)
            {
                for (int j = 0; j < MAP_WIDTH; j++)
                {
                    SDL_Rect obstacle = obstElements[i][j].position;

                    if (obstElements[i][j].symbol != ' ' && SDL_HasIntersection(&bulletRect, &obstacle))
                    {
                        bullet.active_bullet[k] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void CheckGrenadeCollisionWithObstacle(Grenade& grenade, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH])
{
    for (int k = 0; k < grenade.count; k++)
    {
        if (grenade.active_grenade[k])
        {
            SDL_Rect grenadeRect = grenade.grenade_mas[k];

            // Проверка коллизий с препятствиями
            for (int i = 0; i < MAP_HEIGHT; i++)
            {
                for (int j = 0; j < MAP_WIDTH; j++)
                {
                    SDL_Rect obstacle = obstElements[i][j].position;

                    if (obstElements[i][j].symbol != ' ' && SDL_HasIntersection(&grenadeRect, &obstacle))
                    {
                        grenade.is_Moving[k] = 0;
                        break;
                    }
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

bool IsOverlap(int x1, int y1, int x2, int y2, int margin) 
{
    return (x1 - margin < x2 + margin) && (x1 + margin > x2 - margin) &&
        (y1 - margin < y2 + margin) && (y1 + margin > y2 - margin);
}

bool IsOverlapWithOtherEnemies(Enemy* enemies, int currentEnemyIndex, int margin)
{
    for (int i = 0; i < currentEnemyIndex; i++)
    {
        if (IsOverlap(enemies[currentEnemyIndex].position.x, enemies[currentEnemyIndex].position.y,
            enemies[i].position.x, enemies[i].position.y, margin))
        {
            return true;
        }
    }
    return false;
}

bool IsOverlapWithObstacles(int x, int y, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH])
{
    SDL_Rect testRect = { x, y, 81, 100 };

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            SDL_Rect obstacle = obstElements[i][j].position;

            if (obstElements[i][j].symbol != ' ' && SDL_HasIntersection(&testRect, &obstacle))
            {
                return true;
            }
        }
    }

    return false;
}

void InitializeEnemy(Enemy* enemies, Player* player, SDL_Renderer* ren, const char* hectorTexturePath, const char* tucoTexturePath, int x, int y, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH])
{
    srand(time(NULL));

    for (int i = 0; i < MAX_ENEMY; i++)
    {
        Enemy* enemy = &enemies[i];

        int textChance = rand() % 2;
        printf("tCh: %d\n", textChance);
        if (textChance == 0)
        {
            enemy->type = Hector;
            enemy->texture = loadTextureFromFile(hectorTexturePath, &(enemy->position), ren);
        }
        else
        {
            enemy->type = Tuco;
            enemy->texture = loadTextureFromFile(tucoTexturePath, &(enemy->position), ren);
        }

        enemy->position.w = 81;
        enemy->position.h = 100;

        // Генерация случайной позиции для врага
        do {
            enemy->position.x = TILE_SIZE_W + rand() % ((int)WINDOW_WIDTH - enemy->position.w - 1);
            enemy->position.y = TILE_SIZE_H + rand() % ((int)WINDOW_HEIGHT - enemy->position.h - 1);
        } while (IsOverlap(player->position.x, player->position.y, enemy->position.x, enemy->position.y, 70) ||
            IsOverlapWithOtherEnemies(enemies, i, 70) ||
            IsOverlapWithObstacles(enemy->position.x, enemy->position.y, obstElements)); 

        //printf("Pos[%d]: %d %d\n", i, enemy->position.x, enemy->position.y);

        // Остальная инициализация врага

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
}

void RespawnEnemies(Enemy* enemies, Player* player, SDL_Renderer* ren, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (enemies[i].texture)
        {
            SDL_DestroyTexture(enemies[i].texture);
            enemies[i].texture = NULL;
        }
    }
    InitializeEnemy(enemies, player, ren, "HECTOR1.png", "TUCO1.png", 400, 200, obstElements);
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

    if (strcmp(texturePath, "heart.png") == 0)
        bonus->Bontype = Heart;
    else if (strcmp(texturePath, "money.png") == 0)
        bonus->Bontype = Money;
}

void RenderBonus(Bonus bonus, SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, bonus.texture, NULL, &(bonus.position));
}
