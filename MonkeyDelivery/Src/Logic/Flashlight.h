#pragma once
#include "InventoryObject.h"

class Game;

class Flashlight : public InventoryObject
{
private:
	bool active;
public:
	Flashlight(Texture* tex, Game* game);

	bool useObject() override;
	inline bool isOn() { return active; }
	inline void turnOff() { active = false; }
	void setActive(bool b);
};

