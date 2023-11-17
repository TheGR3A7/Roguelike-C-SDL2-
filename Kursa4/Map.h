#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "func.h"

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 12;
extern double TILE_SIZE_W;
extern double TILE_SIZE_H;

struct MapElement {
    char symbol;
    SDL_Texture* texture;
    SDL_Rect position;
};

void LoadMapDataFromFile(const char* surfaceFilename, const char* obstacleFilename);
void LoadSurfaceElements(SDL_Renderer* ren, MapElement surfElements[MAP_HEIGHT][MAP_WIDTH]);
void LoadObstacleElements(SDL_Renderer* ren, MapElement obstElements[MAP_HEIGHT][MAP_WIDTH]);
