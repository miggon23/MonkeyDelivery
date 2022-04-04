#pragma once
#include "InventoryObject.h"

class Player;

// 15% más  velocidad de movimiento durante 30 segundos
// Aumenta la energía un 20% 
class EnergyDrink : public InventoryObject
{

private:
	const float speedBonus_ = 1.15;
	const float energyBonus_ = 1.2;
	const float timeLimit_ = 30000; // 30 seg
public:

	EnergyDrink(Texture* tex, Game* game);
	bool useObject() override;
};

