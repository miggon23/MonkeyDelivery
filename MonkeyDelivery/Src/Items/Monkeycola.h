#pragma once
#include "../Logic/InventoryObject.h"

//Disminuye algo el miedo actual y te lo baja progresivamente durante unos segundos
class Monkeycola : public InventoryObject
{

public:

	Monkeycola(Texture* tex, Game* game, Player* player);
	void setCorrectTexture() override;
	bool useObject() override;
};

