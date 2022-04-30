	#pragma once
#include "../Logic/InventoryObject.h"

class Player;

// 15% más  velocidad de movimiento durante 30 segundos
// Aumenta la energía un 20% 
class EnergyDrink : public InventoryObject{	
public:
	EnergyDrink(Texture* tex, Game* game,Player* player);
	void setCorrectTexture() override;
	bool useObject() override;
};