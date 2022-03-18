#pragma once
#include <vector>

class Player;
class InventoryObject;
class Inventory;
class Game;

class Shop
{
friend class ShopState;

private:
	std::vector <InventoryObject*> objects;
	Player* player;
	Game* game;

public:

	Shop(Player* player, Game* game);
	~Shop();

	void actualice();
	void clearElements();
	void addElements(int level);
	bool buyObject(int id, int price);

	int getSize() { return objects.size(); }

};

