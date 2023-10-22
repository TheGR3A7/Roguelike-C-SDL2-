#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Weapon.h"
#include "Standart values.h"
#include "func.h"

void InitializeWeapons(Weapon weapons[], int numWeapons) 
{
    weapons[0].name = "Knife";
    weapons[0].damage = 10;

    weapons[1].name = "Pistol";
    weapons[1].damage = 20;

    weapons[2].name = "Grenade";
    weapons[2].damage = 50;
}