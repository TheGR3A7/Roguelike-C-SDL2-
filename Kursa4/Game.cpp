#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Game.h"
#include "func.h"
#include "Map.h"


void About(SDL_Renderer* ren)
{
	TTF_Font* fontB = TTF_OpenFont("fonts\\Heart Breaking Bad.otf", 75);
	TTF_Font* fontA = TTF_OpenFont("fonts\\impact.ttf", 75);

	char strAuthor[10] = "autHor";
	char strName[50] = "Alex Logvinov 22-IVT-2";
	char strBack[10] = "Back";

	SDL_Rect Author_rect;
	SDL_Rect Name_rect;
	SDL_Rect Back_rect;

	SDL_Texture* Author_text = NULL;
	SDL_Texture* Name_text = NULL;
	SDL_Texture* Back_text = NULL;

	SDL_Color backButtonNormalColor = { 255, 255, 255, 255 };
	SDL_Color backButtonHoverColor = { 0, 128, 0, 255 };  // Цвет при наведении
	SDL_Color backButtonPressedColor = { 0, 128, 0, 255 };  // Цвет при нажатии

	SDL_Event event;

	while (true)
	{
		while (SDL_PollEvent(&event))  // Используйте переменную event здесь
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					//WINDOW_WIDTH = event.window.data1;
					//WINDOW_HEIGHT = event.window.data2;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				if (PointInRect(mouseX, mouseY, Back_rect))
				{
					backButtonNormalColor = backButtonPressedColor;
					Menu(ren);
					return;
				}
				break;
			case SDL_MOUSEMOTION:
				int mouseXMove, mouseYMove;
				SDL_GetMouseState(&mouseXMove, &mouseYMove);

				if (PointInRect(mouseXMove, mouseYMove, Back_rect)) {
					backButtonNormalColor = backButtonHoverColor;
				}
				else {
					backButtonNormalColor = { 255, 255, 255, 255 };
				}
				break;
			}
		}

		// Отрисовка текста

		if (Author_text != NULL) SDL_DestroyTexture(Author_text);
		Author_text = generateTextureFromText(ren, strAuthor, fontB, &Author_rect, { 255, 255,255,255 });
		Author_rect.x = WINDOW_WIDTH / 2 - Author_rect.w / 2; Author_rect.y = WINDOW_HEIGHT / 4 - Author_rect.h / 2;

		if (Name_text != NULL) SDL_DestroyTexture(Name_text);
		Name_text = generateTextureFromText(ren, strName, fontA, &Name_rect, { 0, 128, 0, 255 });
		Name_rect.x = WINDOW_WIDTH / 2 - Name_rect.w / 2; Name_rect.y = WINDOW_HEIGHT / 3 - Name_rect.h / 2 + 100;

		if (Back_text != NULL) SDL_DestroyTexture(Back_text);
		Back_text = generateTextureFromText(ren, strBack, fontB, &Back_rect, backButtonNormalColor);
		Back_rect.x = WINDOW_WIDTH / 2 - Back_rect.w / 2; Back_rect.y = WINDOW_HEIGHT / 2 - Back_rect.h / 2 + 200;

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Темный фон
		SDL_RenderFillRect(ren, NULL);

		SDL_RenderCopy(ren, Author_text, NULL, &Author_rect);
		SDL_RenderCopy(ren, Name_text, NULL, &Name_rect);
		SDL_RenderCopy(ren, Back_text, NULL, &Back_rect);

		SDL_RenderPresent(ren);
	}
	TTF_CloseFont(fontA);
	TTF_CloseFont(fontB);
}

void Menu(SDL_Renderer* ren)
{
	SDL_Rect Main_Menu_rect;
	SDL_Texture* main_menu = loadTextureFromFile("Menu.jpg", &Main_Menu_rect, ren);

	TTF_Font* font = TTF_OpenFont("fonts\\Heart Breaking Bad.otf", 75);
	char strP[100] = "Play";
	char strA[100] = "aBout";
	char strE[100] = "exIt";

	SDL_Rect Play_rect;
	SDL_Rect About_rect;
	SDL_Rect Exit_rect;
	SDL_Texture* Play_text = NULL;
	SDL_Texture* About_text = NULL;
	SDL_Texture* Exit_text = NULL;

	SDL_Color playButtonNormalColor = { 255, 255, 255, 255 };
	SDL_Color playButtonHoverColor = { 0, 128, 0, 255 };  // Цвет при наведении
	SDL_Color playButtonPressedColor = { 0, 128, 0, 255 };  // Цвет при нажатии
	SDL_Color aboutButtonNormalColor = { 255, 255, 255, 255 };
	SDL_Color aboutButtonHoverColor = { 0, 128, 0, 255 };  // Цвет при наведении
	SDL_Color aboutButtonPressedColor = { 0, 128, 0, 255 };  // Цвет при нажатии
	SDL_Color exitButtonNormalColor = { 255, 255, 255, 255 };
	SDL_Color exitButtonHoverColor = { 0, 128, 0, 255 };  // Цвет при наведении
	SDL_Color exitButtonPressedColor = { 0, 128, 0, 255 };  // Цвет при нажатии

	SDL_Event event;

	while (true)
	{
		while (SDL_PollEvent(&event))  // Используйте переменную event здесь
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					//WINDOW_WIDTH = event.window.data1;
					//WINDOW_HEIGHT = event.window.data2;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				if (PointInRect(mouseX, mouseY, Play_rect))
				{
					playButtonNormalColor = playButtonPressedColor;
					Game(ren);
					return;
				}
				else if (PointInRect(mouseX, mouseY, About_rect))
				{
					aboutButtonNormalColor = aboutButtonPressedColor;
					About(ren);
					return;
				}
				else if (PointInRect(mouseX, mouseY, Exit_rect))
				{
					exitButtonNormalColor = exitButtonPressedColor;
					return;
				}
				break;
			case SDL_MOUSEMOTION:
				int mouseXMove, mouseYMove;
				SDL_GetMouseState(&mouseXMove, &mouseYMove);

				if (PointInRect(mouseXMove, mouseYMove, Play_rect)) {
					playButtonNormalColor = playButtonHoverColor;
				}
				else{
					playButtonNormalColor = { 255, 255, 255, 255 };  
				}
				if (PointInRect(mouseXMove, mouseYMove, About_rect)) {
					aboutButtonNormalColor = aboutButtonHoverColor;
				}
				else {
					aboutButtonNormalColor = { 255, 255, 255, 255 };  
				}
				if (PointInRect(mouseXMove, mouseYMove, Exit_rect)) {
					exitButtonNormalColor = exitButtonHoverColor;
				}
				else {
					exitButtonNormalColor = { 255, 255, 255, 255 };
				}
				break;
			}
		}
		// Отрисовка текста

		if (Play_text != NULL) SDL_DestroyTexture(Play_text);
		Play_text = generateTextureFromText(ren, strP, font, &Play_rect, playButtonNormalColor);
		Play_rect.x = WINDOW_WIDTH / 2 - Play_rect.w / 2; Play_rect.y = WINDOW_HEIGHT / 2 - Play_rect.h / 2;

		if (About_text != NULL) SDL_DestroyTexture(About_text);
		About_text = generateTextureFromText(ren, strA, font, &About_rect, aboutButtonNormalColor);
		About_rect.x = WINDOW_WIDTH / 2 - About_rect.w / 2; About_rect.y = WINDOW_HEIGHT / 2 - About_rect.h / 2 + 100;

		if (Exit_text != NULL) SDL_DestroyTexture(Exit_text);
		Exit_text = generateTextureFromText(ren, strE, font, &Exit_rect, exitButtonNormalColor);
		Exit_rect.x = WINDOW_WIDTH / 2 - Exit_rect.w / 2; Exit_rect.y = WINDOW_HEIGHT / 2 - Exit_rect.h / 2 + 200;

		SDL_RenderCopy(ren, main_menu, NULL, NULL);
		SDL_RenderCopy(ren, Play_text, NULL, &Play_rect);
		SDL_RenderCopy(ren, About_text, NULL, &About_rect);
		SDL_RenderCopy(ren, Exit_text, NULL, &Exit_rect);

		SDL_RenderPresent(ren);
		SDL_Delay(16);
	}
	TTF_CloseFont(font);
}


bool PointInRect(int x, int y, const SDL_Rect& rect)
{
	return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

void CollisionWithBullet(Player& player, Bullet& bullet, Enemy enemy[], Bonus bonus[], SDL_Renderer* ren)
{
	for (int i = 0; i < 2; i++)
			for (int k = 0; k < bullet.count; k++)
				if (bullet.active_bullet[k] == 1)
					if (bullet.bullet_mas[k].y <= enemy[i].position.y + enemy[i].position.h && bullet.bullet_mas[k].y + bullet.size_y >= enemy[i].position.y)
						if (bullet.bullet_mas[k].x <= enemy[i].position.x + enemy[i].position.w && bullet.bullet_mas[k].x + bullet.size_x >= enemy[i].position.x)
						{
							enemy[i].hp -= bullet.dmg;
							if (enemy[i].hp <= 0)
							{
								for (int j = 0; j < 5; j++)
									if (bonus[j].position.y >= WINDOW_HEIGHT + 1)
									{
										bonus[j].position.x = enemy[i].position.x + enemy[i].position.w / 2;
										bonus[j].position.y = enemy[i].position.y + enemy[i].position.h / 2;
										break;
									}
								enemy[i].position.y = WINDOW_HEIGHT + 1;
							}
							bullet.active_bullet[k] = 0;
						}
}

void CollisionWithBonus(Player& player, Bonus bonus[])
{
	for (int i = 0; i < 5; i++)
	if (player.position.y <= bonus[i].position.y + bonus[i].position.h && player.position.y + player.position.h >= bonus[i].position.y)
		if (player.position.x <= bonus[i].position.x + bonus[i].position.w && player.position.x + player.position.w >= bonus[i].position.x)
		{
			if (player.hp + 25 <= player.maxhp)
				player.hp += 25;
			else
				player.hp = player.maxhp;
			if (player.money + 25 <= player.maxmoney)
				player.money += 25;
			else
				player.money = player.maxmoney;
			bonus[i].position.x = 0;
			bonus[i].position.y = WINDOW_HEIGHT + 1;
		}
}

void RenderGameText(TTF_Font* font, Player* player, SDL_Renderer* ren)
{
	char strHP[10] = "HP: ";
	char strMON[10] = "MON: ";
	char HPval[10];
	char MONval[10];

	sprintf(HPval, "%d", player->hp);
	sprintf(MONval, "%d", player->money);

	SDL_Rect HP_rect;
	SDL_Rect MON_rect;
	SDL_Rect HP_shadow;
	SDL_Rect MON_shadow;
	SDL_Rect HP_value;
	SDL_Rect MON_value;
	SDL_Rect HP_valueshadow;
	SDL_Rect MON_valueshadow;

	SDL_Texture* HP_text = NULL;
	SDL_Texture* MON_text = NULL;
	SDL_Texture* HP_shadowtext = NULL;
	SDL_Texture* MON_shadowtext = NULL;
	SDL_Texture* HP_valuetext = NULL;
	SDL_Texture* MON_valuetext = NULL;
	SDL_Texture* HP_valueshadowtext = NULL;
	SDL_Texture* MON_valueshadowtext = NULL;

	if (HP_shadowtext != NULL) SDL_DestroyTexture(HP_shadowtext);
	HP_shadowtext = generateTextureFromText(ren, strHP, font, &HP_shadow, { 0, 0,0,255 });
	HP_shadow.x = 10; HP_shadow.y = 10; HP_shadow.w = 80; HP_shadow.h = 55;

	if (HP_text != NULL) SDL_DestroyTexture(HP_text);
	HP_text = generateTextureFromText(ren, strHP, font, &HP_rect, { 255, 0,0,255 });
	HP_rect.x = 10; HP_rect.y = 10; HP_rect.w = 75; HP_rect.h = 50;

	if (MON_shadowtext != NULL) SDL_DestroyTexture(MON_shadowtext);
	MON_shadowtext = generateTextureFromText(ren, strMON, font, &MON_shadow, { 0, 0,0,255 });
	MON_shadow.x = 10; MON_shadow.y = 50; MON_shadow.w = 80; MON_shadow.h = 55;

	if (MON_text != NULL) SDL_DestroyTexture(MON_text);
	MON_text = generateTextureFromText(ren, strMON, font, &MON_rect, { 255, 255,0,255 });
	MON_rect.x = 10; MON_rect.y = 50; MON_rect.w = 75; MON_rect.h = 50;

	if (HP_valueshadowtext != NULL) SDL_DestroyTexture(HP_valueshadowtext);
	HP_valueshadowtext = generateTextureFromText(ren, HPval, font, &HP_valueshadow, { 0, 0,0,255 });
	HP_valueshadow.x = HP_rect.x + HP_rect.w + 10; HP_valueshadow.y = HP_rect.y; HP_valueshadow.w = 55; HP_valueshadow.h = 55;

	if (HP_valuetext != NULL) SDL_DestroyTexture(HP_valuetext);
	HP_valuetext = generateTextureFromText(ren, HPval, font, &HP_value, { 255, 0,0,255 });
	HP_value.x = HP_rect.x + HP_rect.w + 10; HP_value.y = HP_rect.y; HP_value.w = 50; HP_value.h = 50;

	if (MON_valueshadowtext != NULL) SDL_DestroyTexture(MON_valueshadowtext);
	MON_valueshadowtext = generateTextureFromText(ren, MONval, font, &MON_valueshadow, { 0, 0,0,255 });
	MON_valueshadow.x = MON_rect.x + MON_rect.w + 10; MON_valueshadow.y = MON_rect.y; MON_valueshadow.w = 55; MON_valueshadow.h = 55;

	if (MON_valuetext != NULL) SDL_DestroyTexture(MON_valuetext);
	MON_valuetext = generateTextureFromText(ren, MONval, font, &MON_value, { 255, 255,0,255 });
	MON_value.x = MON_rect.x + MON_rect.w + 10; MON_value.y = MON_rect.y; MON_value.w = 50; MON_value.h = 50;


	SDL_RenderCopy(ren, HP_shadowtext, NULL, &HP_shadow);
	SDL_RenderCopy(ren, HP_text, NULL, &HP_rect);
	SDL_RenderCopy(ren, MON_shadowtext, NULL, &MON_shadow);
	SDL_RenderCopy(ren, MON_text, NULL, &MON_rect);
	SDL_RenderCopy(ren, HP_valueshadowtext, NULL, &HP_valueshadow);
	SDL_RenderCopy(ren, HP_valuetext, NULL, &HP_value);
	SDL_RenderCopy(ren, MON_valueshadowtext, NULL, &MON_valueshadow);
	SDL_RenderCopy(ren, MON_valuetext, NULL, &MON_value);

	SDL_DestroyTexture(HP_valuetext);
	SDL_DestroyTexture(MON_valuetext);
	SDL_DestroyTexture(HP_valueshadowtext);
	SDL_DestroyTexture(MON_valueshadowtext);
}

void DeadWallpaper(Player*player, SDL_Renderer* ren)
{	
		TTF_Font* fontB = TTF_OpenFont("fonts\\Heart Breaking Bad.otf", 75);
		TTF_Font* fontA = TTF_OpenFont("fonts\\impact.ttf", 75);

		char strDEAD[10] = "DEAD";
		char strBack[10] = "Back";

		SDL_Rect DEAD_rect;
		SDL_Texture* DEAD_text = NULL;
		SDL_Rect Back_rect;
		SDL_Texture* Back_text = NULL;

		SDL_Color backButtonNormalColor = { 255, 255, 255, 255 };
		SDL_Color backButtonHoverColor = { 0, 128, 0, 255 };  // Цвет при наведении
		SDL_Color backButtonPressedColor = { 0, 128, 0, 255 };  // Цвет при нажатии

		SDL_Event event;

		while (true)
		{
			while (SDL_PollEvent(&event))  // Используйте переменную event здесь
			{
				switch (event.type)
				{
				case SDL_QUIT:
					return;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						//WINDOW_WIDTH = event.window.data1;
						//WINDOW_HEIGHT = event.window.data2;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					if (PointInRect(mouseX, mouseY, Back_rect))
					{
						backButtonNormalColor = backButtonPressedColor;
						Menu(ren);
						return;
					}
					break;
				case SDL_MOUSEMOTION:
					int mouseXMove, mouseYMove;
					SDL_GetMouseState(&mouseXMove, &mouseYMove);

					if (PointInRect(mouseXMove, mouseYMove, Back_rect)) {
						backButtonNormalColor = backButtonHoverColor;
					}
					else {
						backButtonNormalColor = { 255, 255, 255, 255 };
					}
					break;
				}
			}

			// Отрисовка текста

			if (DEAD_text != NULL) SDL_DestroyTexture(DEAD_text);
			DEAD_text = generateTextureFromText(ren, strDEAD, fontA, &DEAD_rect, { 255, 0,0,255 });
			DEAD_rect.x = WINDOW_WIDTH / 2 - DEAD_rect.w / 2; DEAD_rect.y = WINDOW_HEIGHT / 2 - DEAD_rect.h / 2;

			if (Back_text != NULL) SDL_DestroyTexture(Back_text);
			Back_text = generateTextureFromText(ren, strBack, fontB, &Back_rect, backButtonNormalColor);
			Back_rect.x = WINDOW_WIDTH / 2 - Back_rect.w / 2; Back_rect.y = WINDOW_HEIGHT / 2 - Back_rect.h / 2 + 200;

			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Темный фон
			SDL_RenderFillRect(ren, NULL);

			SDL_RenderCopy(ren, DEAD_text, NULL, &DEAD_rect);
			SDL_RenderCopy(ren, Back_text, NULL, &Back_rect);

			SDL_RenderPresent(ren);
		}
		TTF_CloseFont(fontA);
		TTF_CloseFont(fontB);
}



void Game(SDL_Renderer* ren)
{
	TTF_Font* font = TTF_OpenFont("fonts\\impact.ttf", 75);

	bool isRunning = true;
	bool is_cooldown = true;
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
    InitializePlayer(&player, ren, "HEISENBERG1.png", 100, 100);

	Enemy enemy[2];

	Enemy hector;
	InitializeEnemy(&enemy[0], ren, "HECTOR1.png", 400, 200);

	Enemy tuco;
	InitializeEnemy(&enemy[1], ren, "TUCO1.png", 300, 300);

	Bullet bullet;
	CreateBullet(bullet, player, ren);

	Bonus bonus[5];
	for(int i = 0; i<5; i++)
		InitializeBonus(&bonus[i], ren, "heart.png", 0, WINDOW_HEIGHT + 1);

	//Bonus bonusHP[5];
	//for(int i = 0; i<5; i++)
	//	InitializeBonus(&bonusHP[i], ren, "heart.png", 0, WINDOW_HEIGHT + 1);
	//Bonus bonusMON[5];
	//for (int i = 0; i < 5; i++)
	//	InitializeBonus(&bonusMON[i], ren, "money.png", 0, WINDOW_HEIGHT + 1);
	

	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;

    while (isRunning) 
    {

		if (!CheckCooldown(bullet, 16))
			is_cooldown = false;

        SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{

			switch (ev.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					//WINDOW_WIDTH = ev.window.data1;
					//WINDOW_HEIGHT = ev.window.data2;
				}
				break;
				
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					Menu(ren);
					break;
				case SDL_SCANCODE_1:
					player.currentWeapon.name = "Knife";
					InitializePlayer(&player, ren, "HEISENBERGKnife1.png", player.position.x, player.position.y);
					break;
				case SDL_SCANCODE_2:
					player.currentWeapon.name = "Pistol";
					InitializePlayer(&player, ren, "HEISENBERGPistol1.png", player.position.x, player.position.y);
					break;
				case SDL_SCANCODE_3:
					player.currentWeapon.name = "Grenade";
					InitializePlayer(&player, ren, "HEISENBERGGrenade1.png", player.position.x, player.position.y);
					break;
				case SDL_SCANCODE_SPACE:
					if (player.currentWeapon.name == "Pistol")
					{
						for (int i = 0; i < MAX_BULLETS; i++)
							if (bullet.active_bullet[i] == 0 && !is_cooldown)
							{
								bullet.bulletDirection[i] = player.direction; 
 								bullet.active_bullet[i] = 1;
								is_cooldown = true;
								break;
							}
						BulletSpawn(bullet, &player);
					}
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
		UpdatePlayer(&player, isUpPressed, isDownPressed, isLeftPressed, isRightPressed, obstElements, enemy);

		BulletMovement(bullet, &player, 16);

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

        // Отрисовка игрока, врагов и тд

		for(int i = 0; i <5;i++)
			RenderBonus(bonus[i], ren);
		//for(int i = 0; i <5;i++)
		//	RenderBonus(bonusHP[i], ren);
		//for (int i = 0; i < 5; i++)
		//	RenderBonus(bonusMON[i], ren);

		RenderPlayer(&player, ren);

		RenderEnemy(&enemy[0], ren);
		RenderEnemy(&enemy[1], ren);

		CollisionWithBullet(player, bullet,enemy, bonus, ren);
		CollisionWithBonus(player, bonus);

		BulletDraw(bullet, ren);

		RenderGameText(font, &player, ren);

		if (player.hp <= 0)
		{
			DeadWallpaper(&player, ren);
			break; 
		}

        // Обновление экрана
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

	TTF_CloseFont(font);
    CleanUpPlayer(&player);
}
