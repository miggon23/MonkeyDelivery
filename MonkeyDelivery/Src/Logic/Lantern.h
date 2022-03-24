#pragma once
#include "InventoryObject.h"

class Game;

class Lantern : public InventoryObject
{
private:
	bool active;
public:
	Lantern(Texture* tex);

	bool useObject() override;
	inline bool isOn() { return active; }
	inline void turnOff() { active = false; }
};

