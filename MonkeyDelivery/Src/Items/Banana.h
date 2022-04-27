#pragma once

#include "../Logic/InventoryObject.h"

class Banana : public InventoryObject {
public:
	Banana(Texture* tex, Game* game, Player* player);
	bool useObject() override;
};

