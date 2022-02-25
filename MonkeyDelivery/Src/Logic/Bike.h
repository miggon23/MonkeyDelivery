#pragma once
#include "InventoryObject.h"

class Game;

class Bike : public InventoryObject
{
private:
	bool active;
	double speedMult;
public:
	Bike(Game* game);
	~Bike();

	bool useObject() override;
};

