#pragma once
#include "../Logic/InventoryObject.h"

class Monkeycola : public InventoryObject
{

public:

	Monkeycola(Texture* tex, Game* game, Player* player);
	bool useObject() override;
};

