#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Game.h"
#include "func.h"
#include "Player.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 12
#define TILE_SIZE 50

char surfData[MAP_HEIGHT][MAP_WIDTH];
char obstData[MAP_HEIGHT][MAP_WIDTH];

void LoadMapDataFromFile(const char* surfaceFilename, const char* obstacleFilename)
{
	FILE* surfaceFile = fopen(surfaceFilename, "r");
	if (surfaceFile == NULL)
	{
		printf("Не удалось открыть файл с данными карты.\n");
		exit(1);
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			char symbol;

			while (fscanf(surfaceFile, "%c", &symbol) == 1)
			{
				if (symbol != ' ' && symbol != '\n')
				{
					surfData[i][j] = symbol;
					break;
				}
			}
		}
	}

	fclose(surfaceFile);

	FILE* obstacleFile = fopen(obstacleFilename, "r");
	if (obstacleFile == NULL)
	{
		printf("Не удалось открыть файл с данными карты.\n");
		exit(1);
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			char symbol;

			while (fscanf(obstacleFile, "%c", &symbol) == 1)
			{
				if ( symbol != '\n')
				{
					obstData[i][j] = symbol;
					break;
				}
			}
		}
	}

	fclose(obstacleFile);
}



void LoadSurfaceElements(SDL_Renderer* ren, MapElement surfElements[MAP_HEIGHT][MAP_WIDTH])
{
	for (int i = 0; i < MAP_HEIGHT; i++) 
	{
		for (int j = 0; j < MAP_WIDTH; j++) 
		{
			char symbol = surfData[i][j]; 
			if (symbol == '.') {
				surfElements[i][j].texture = loadTextureFromFile("asphalt.jpg", &(surfElements[i][j].position), ren);
			}
			else if (symbol == ',') {
				surfElements[i][j].texture = loadTextureFromFile("light_tile.jpg", &(surfElements[i][j].position), ren);
			}
			else if (symbol == '"') {
				surfElements[i][j].texture = loadTextureFromFile("sidewalk.png", &(surfElements[i][j].position), ren);
			}
			surfElements[i][j].position.x = j * TILE_SIZE;
			surfElements[i][j].position.y = i * TILE_SIZE;
			surfElements[i][j].position.w = TILE_SIZE;
			surfElements[i][j].position.h = TILE_SIZE;
			surfElements[i][j].symbol = symbol;
		}
	}
}

void LoadObstacleElements(SDL_Renderer* ren, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH])
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			char symbol = obstData[i][j];
			if (symbol == '#')
			{
				obstElements[i][j].texture = loadTextureFromFile("wall.png", &(obstElements[i][j].position), ren);
			}
			else if (symbol == '/') {
				obstElements[i][j].texture = loadTextureFromFile("door.png", &(obstElements[i][j].position), ren);
			}
			else if (symbol == '=') {
				obstElements[i][j].texture = loadTextureFromFile("fence_h.png", &(obstElements[i][j].position), ren);
			}
			else if (symbol == '|') {
				obstElements[i][j].texture = loadTextureFromFile("fence_v.png", &(obstElements[i][j].position), ren);
			}
			else if (symbol == '*') {
				obstElements[i][j].texture = loadTextureFromFile("roof.png", &(obstElements[i][j].position), ren);
			}
			else if (symbol == ' ') {
				obstElements[i][j].texture = nullptr;
			}
			obstElements[i][j].position.x = j * TILE_SIZE;
			obstElements[i][j].position.y = i * TILE_SIZE;
			obstElements[i][j].position.w = TILE_SIZE;
			obstElements[i][j].position.h = TILE_SIZE;
			obstElements[i][j].symbol = symbol;
		}
	}
}

// Loc 1: y (200, 400), x>1000
// Loc 2: y (200, 400), x<1000 || y (50, 550), x > 1000
// Loc 3: y (50, 550), x < 1000

void CheckLocation(Player& player, SDL_Renderer* ren, MapElement surfElements[MAP_HEIGHT][MAP_WIDTH], MapElement obstElements[MAP_HEIGHT][MAP_WIDTH], int& currentLocation)
{
	if (currentLocation == 1) 
	{
		if ((player.position.y >= 250 - (player.position.h/2))&& (player.position.x >= WINDOW_WIDTH - (player.position.w/2)) && (player.position.y <= 400 - (player.position.h-15)))
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
		if ((player.position.y >= 250 - (player.position.h / 2)) && (player.position.x <= 0 - (player.position.w / 2)) && (player.position.y <= 400 - (player.position.h-15)))
		{
			currentLocation = 1;
			LoadMapDataFromFile("surfLoc1.txt", "obstLoc1.txt");
			LoadSurfaceElements(ren, surfElements);
			LoadObstacleElements(ren, obstElements);
			player.position.x = 900;
		}
		else if ((player.position.y >= 50 - (player.position.h / 2)) && (player.position.x >= WINDOW_WIDTH - (player.position.w / 2)) && (player.position.y <= 400 + (player.position.h - 15)))
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
		if ((player.position.y >= 50 - (player.position.h / 2)) && (player.position.x <= 0 - (player.position.w / 2)) && (player.position.y <= 400 + (player.position.h - 15)))
		{
			currentLocation = 2;
			LoadMapDataFromFile("surfLoc2.txt", "obstLoc2.txt");
			LoadSurfaceElements(ren, surfElements);
			LoadObstacleElements(ren, obstElements);
			player.position.x = 900;
		}
	}
}


void Game(SDL_Renderer* ren)
{
	bool isRunning = true;
	int currentLocation = 1;

	// Загрузка данных карты из файла
	LoadMapDataFromFile("surfLoc1.txt", "obstLoc1.txt");

	// Создание массива для элементов карты
	MapElement surfElements[MAP_HEIGHT][MAP_WIDTH]; 
	MapElement obstElements[MAP_HEIGHT][MAP_WIDTH];

	// Загрузка текстур элементов карты
	LoadSurfaceElements(ren, surfElements);
	LoadObstacleElements(ren, obstElements);

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
		CheckLocation(player, ren, surfElements, obstElements, currentLocation);

        // Очистка экрана
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

		// Отрисовка элементов карты
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				SDL_RenderCopy(ren, surfElements[i][j].texture, NULL, &(surfElements[i][j].position));
				if(obstElements[i][j].texture != nullptr)
					SDL_RenderCopy(ren, obstElements[i][j].texture, NULL, &(obstElements[i][j].position));
			}
		}

        // Отрисовка игрока, врагов
		RenderPlayer(&player, ren);

		RenderEnemy(&hector, ren);
		RenderEnemy(&tuco, ren);

        // Обновление экрана
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    CleanUpPlayer(&player);
}
