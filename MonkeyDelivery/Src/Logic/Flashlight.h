#pragma once
#include "InventoryObject.h"

class Game;

class Flashlight : public InventoryObject
{
private:
	bool active;
public:
	Flashlight();

	bool useObject() override;
	SDL_Rect lightZone();
};

