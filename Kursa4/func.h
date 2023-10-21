#pragma once

#include <SDL.h>

SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect, SDL_Renderer* ren);
SDL_Texture* generateTextureFromText(SDL_Renderer* ren, const char* str, TTF_Font* font, SDL_Rect* rect, SDL_Color fg);
void DeInit(int error, SDL_Window** win, SDL_Renderer** ren, SDL_Surface** win_surface);
void Init(SDL_Window** win, SDL_Renderer** ren, SDL_Surface** win_surface, int WINDOW_HEIGHT, int WINDOW_WIDTH);
