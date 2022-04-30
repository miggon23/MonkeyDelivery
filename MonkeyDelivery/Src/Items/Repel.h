#pragma once
#include "../Logic/InventoryObject.h"

class Repel : public InventoryObject{
public:
	Repel(Texture* tex, Game* game, Player* player);
	void setCorrectTexture() override;
	bool useObject() override;
};

