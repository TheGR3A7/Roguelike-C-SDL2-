#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Map.h"
#include "func.h"


double TILE_SIZE_W = 50;
double TILE_SIZE_H = 50;


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
				if (symbol != '\n')
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
			surfElements[i][j].position.x = j * TILE_SIZE_W;
			surfElements[i][j].position.y = i * TILE_SIZE_H;
			surfElements[i][j].position.w = TILE_SIZE_W;
			surfElements[i][j].position.h = TILE_SIZE_H;
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
			obstElements[i][j].position.x = j * TILE_SIZE_W;
			obstElements[i][j].position.y = i * TILE_SIZE_H;
			obstElements[i][j].position.w = TILE_SIZE_W;
			obstElements[i][j].position.h = TILE_SIZE_H;
			obstElements[i][j].symbol = symbol;
		}
	}
}

