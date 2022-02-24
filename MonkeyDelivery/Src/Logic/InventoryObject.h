#pragma once

class Game;

class InventoryObject
{
private:
	Game* game_ = nullptr;
public:
	InventoryObject(Game * game);
	~InventoryObject();

	virtual bool useObject();
};

