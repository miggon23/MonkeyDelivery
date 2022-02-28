#pragma once

class Game;
class Player;

class InventoryObject
{
protected:
	Player* player_ = nullptr;
public:

	virtual bool useObject();
	void attachPlayer(Player* player);
};

