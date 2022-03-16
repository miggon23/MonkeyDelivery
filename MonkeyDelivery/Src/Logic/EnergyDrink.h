#pragma once
#include "InventoryObject.h"

class Player;

// 15% más  velocidad de movimiento durante 30 segundos
// Aumenta la energía un 20% 
class EnergyDrink : public InventoryObject
{
public:

	EnergyDrink() { isConsumable_ = true; };
	bool useObject() override;
};

