#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Game.h"
#include "func.h"
#include "Player.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 8
#define TILE_SIZE 25

char mapData[MAP_HEIGHT][MAP_WIDTH];

void LoadMapDataFromFile(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Не удалось открыть файл с данными карты.\n");
		exit(1);
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			char symbol;

			while (fscanf(file, "%c", &symbol) == 1)
			{
				if (symbol != ' ' && symbol != '\n')
				{
					mapData[i][j] = symbol;
					break;
				}
			}
		}
	}

	fclose(file);
}



void LoadMapElements(SDL_Renderer* ren, MapElement mapElements[MAP_WIDTH][MAP_HEIGHT])
{
	for (int i = 0; i < MAP_WIDTH; i++) 
	{
		for (int j = 0; j < MAP_HEIGHT; j++) 
		{
			mapElements[i][j].position.x = i * TILE_SIZE;
			mapElements[i][j].position.y = j * TILE_SIZE;
			mapElements[i][j].position.w = TILE_SIZE;
			mapElements[i][j].position.h = TILE_SIZE;
			char symbol = mapData[i][j]; // Инвертируйте индексы, если необходимо
			if (symbol == '#') 
			{
				mapElements[i][j].texture = loadTextureFromFile("wall.png", &(mapElements[i][j].position), ren); 
			}
			else if (symbol == '/') {
				mapElements[i][j].texture = loadTextureFromFile("door.png", &(mapElements[i][j].position), ren);
			}
			else if (symbol == '.') {
				mapElements[i][j].texture = loadTextureFromFile("asphalt.jpg", &(mapElements[i][j].position), ren);
			}
			else if (symbol == '=') {
				mapElements[i][j].texture = loadTextureFromFile("fence_h.png", &(mapElements[i][j].position), ren);
			}
			else if (symbol == '|') {
				mapElements[i][j].texture = loadTextureFromFile("fence_v.png", &(mapElements[i][j].position), ren);
			}
			else if (symbol == ',') {
				mapElements[i][j].texture = loadTextureFromFile("light_tile.jpg", &(mapElements[i][j].position), ren);
			}
			else if (symbol == '"') {
				mapElements[i][j].texture = loadTextureFromFile("sidewalk.png", &(mapElements[i][j].position), ren);
			}
			else if (symbol == '*') {
				mapElements[i][j].texture = loadTextureFromFile("roof.png", &(mapElements[i][j].position), ren);
			}
			mapElements[i][j].symbol = symbol;
		}
	}
}



void Game(SDL_Renderer* ren)
{
	bool isRunning = true;

	// Загрузка данных карты из файла
	LoadMapDataFromFile("map.txt");

	// Создание массива для элементов карты
	MapElement mapElements[MAP_WIDTH][MAP_HEIGHT];

	// Загрузка текстур элементов карты
	LoadMapElements(ren, mapElements);

    Player player;
    InitializePlayer(&player, ren, "HeisDef.png", 100, 100);

	Enemy hector;
	InitializeEnemy(&hector, ren, "Hector.png", 200, 200);

	Enemy tuco;
	InitializeEnemy(&tuco, ren, "Tuco.png", 300, 300);

	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;

    while (isRunning) 
    {
        SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{

			switch (ev.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_1:
					player.currentWeapon.name = "Knife";
					InitializePlayer(&player, ren, "HeisKnife.png", player.position.x, player.position.y);
					break;
				case SDL_SCANCODE_2:
					player.currentWeapon.name = "Pistol";
					InitializePlayer(&player, ren, "HeisPistol.png", player.position.x, player.position.y);
					break;
				case SDL_SCANCODE_3:
					player.currentWeapon.name = "Grenade";
					InitializePlayer(&player, ren, "HeisGrenade.png", player.position.x, player.position.y);
					break;
				case SDL_SCANCODE_SPACE:


					break;
				case SDL_SCANCODE_W:
					isUpPressed = true;
					break;
				case SDL_SCANCODE_S:
					isDownPressed = true;
					break;
				case SDL_SCANCODE_D:
					isRightPressed = true;
					player.direction = DIR_RIGHT;
					break;
				case SDL_SCANCODE_A:
					isLeftPressed = true;
					player.direction = DIR_LEFT;
					break;
				}
				break;

			case SDL_KEYUP:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					isUpPressed = false;
					break;
				case SDL_SCANCODE_S:
					isDownPressed = false;
					break;
				case SDL_SCANCODE_D:
					isRightPressed = false;
					break;
				case SDL_SCANCODE_A:
					isLeftPressed = false;
					break;
				}
				break;
			}
		}

        // Обновление игрока
        UpdatePlayer(&player, isUpPressed, isDownPressed, isLeftPressed, isRightPressed);


        // Очистка экрана
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

		// Отрисовка элементов карты
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			for (int j = 0; j < MAP_HEIGHT; j++)
			{
				SDL_RenderCopy(ren, mapElements[i][j].texture, NULL, &(mapElements[i][j].position));
			}
		}

        // Отрисовка игрока
		RenderPlayer(&player, ren);

		RenderEnemy(&hector, ren);
		RenderEnemy(&tuco, ren);

        // Обновление экрана
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    CleanUpPlayer(&player);
}
