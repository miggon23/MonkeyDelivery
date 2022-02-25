#pragma once

class Game;
class Player;

class InventoryObject
{
protected:
	Game* game_ = nullptr;
	Player* player_ = nullptr;
public:
	InventoryObject(Game * game);
	~InventoryObject();

	virtual bool useObject();
	void attachPlayer(Player* player);
};

