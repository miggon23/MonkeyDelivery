#pragma once
#include <vector>

class Player;
class InventoryObject;
class Inventory;
class Shop
{
private:
	std::vector <InventoryObject*> objects;
	Player* player;

public:

	Shop(Player* player);
	~Shop();

	void actualice();
	void clearElements();
	void addElements(int level);
	bool buyObject(int id, int price);

};

