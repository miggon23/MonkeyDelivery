#pragma once
#include "InventoryObject.h"

class Player;

class Pickaxe : public InventoryObject{
private:
	int uses_;//regula el uso del pico
public:
	Pickaxe(Texture* tex, Game* game);
	bool useObject() override;
};