#pragma once
#include "InventoryObject.h"

class Game;
class Flashlight;

class Lantern : public InventoryObject
{
public:
	Lantern(Texture* tex, Game* game);

	bool useObject() override;
	inline bool isOn() { return active; }
	inline void turnOff() { active = false; }
};