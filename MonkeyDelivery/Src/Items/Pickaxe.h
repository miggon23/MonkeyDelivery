#pragma once
#include "../Logic/InventoryObject.h"

class Player;

class Pickaxe : public InventoryObject{
private:
	int level_;//el nivel del pico
public:
	Pickaxe(Texture* tex, Game* game,int level,Player* player);
	void setCorrectTexture() override;
	bool useObject() override;
};