#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "func.h"
#include "Player.h"

struct MapElement {
    char symbol;
    SDL_Texture* texture;
    SDL_Rect position;
};

void Game(SDL_Renderer* ren);
