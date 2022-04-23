#pragma once
#include "../Logic/InventoryObject.h"

class Game;

class Flashlight : public InventoryObject
{
public:
	Flashlight(Texture* tex, Game* game,Player* player);

	bool useObject() override;
	inline bool isOn() { return active; }
	inline void turnOff() { active = false; }
	void setActive(bool b);
};