#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_TTF.h>
#include <iostream>
#include <math.h>
#include "Game.h"

//- управление(движение +, клавиши оружие +, клавиша для хилла(на 4), пробел для стрельбы)
//- главное меню(start, about, exit)
//- минимум 3 типа оружия(нож, пистолет, граната)
//- минимум 2 типа противников(пистолет, камикадзе)
//- загрузка карты с файла
//- минимум 3 локации
//- простейшие выпадающие бонусы из противников(здоровье, деньги и тд.)

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surface = NULL;

void WindowDelay()
{
	static int time = 0;
	while (true)
	{
		if (clock() - time >= 1000 / FPS)
		{
			time = clock();
			break;
		}
		else
			SDL_Delay(1);
	}
}


int main(int argc, char* argv[])
{
	system("chcp 1251");
	Init(&win, &ren, &win_surface, WINDOW_HEIGHT, WINDOW_WIDTH);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	Game(ren);

	DeInit(0, &win, &ren, &win_surface);

	return 0;
}