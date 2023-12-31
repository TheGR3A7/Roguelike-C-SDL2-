#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_TTF.h>
#include <iostream>
#include <math.h>
#include "Game.h"


SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surface = NULL;


int main(int argc, char* argv[])
{
	system("chcp 1251");
	Init(&win, &ren, &win_surface, WINDOW_HEIGHT, WINDOW_WIDTH);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	Menu(ren);

	DeInit(0, &win, &ren, &win_surface);

	return 0;
}