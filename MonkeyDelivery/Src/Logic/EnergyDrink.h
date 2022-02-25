#pragma once
#include "InventoryObject.h"

class Game;
class Player;

class EnergyDrink : public InventoryObject
{
public:
	EnergyDrink(Game *game);
	~EnergyDrink();	

	bool useObject() override;
};

