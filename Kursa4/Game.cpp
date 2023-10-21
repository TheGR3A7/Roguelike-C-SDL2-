#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "func.h"
#include "Player.h"


void Game(SDL_Renderer* ren)
{
	bool isRunning = true;

    Player player;
    InitializePlayer(&player, ren, "HeisDef.png", 100, 100);

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

        // Отрисовка игрока
        //RenderPlayer(&player, ren);

		if (player.direction == DIR_RIGHT)
		{
			RenderPlayer(&player, ren);
		}
		else
		{
			RenderPlayer(&player, ren);
		}

        // Обновление экрана
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    CleanUpPlayer(&player);
}
