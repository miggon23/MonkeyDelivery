#pragma once
#include "InventoryObject.h"

class Player;

class EnergyDrink : public InventoryObject
{
public:

	bool useObject() override;
};

