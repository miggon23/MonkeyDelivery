#pragma once
#include "InventoryObject.h"

class Game;

class Flashlight : public InventoryObject
{
private:
	bool active;
public:
	Flashlight();

	bool useObject() override;
	inline bool isOn() { return active; }
};

