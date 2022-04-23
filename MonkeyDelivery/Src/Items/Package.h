#pragma once
#include "../Logic/InventoryObject.h"

class Package : public InventoryObject
{
public:
	Package(Texture* tex, Game* game,Player* player);
	~Package() {};
	inline bool useObject() override { return false; }; // no se llamará nunca -> los paquetes no se usan

private:
	
};