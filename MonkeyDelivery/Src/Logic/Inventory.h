#pragma once

#include <vector>

using namespace std;

class InventoryObject;
class Player;

class Inventory
{
private:
	const int INVENTORY_SIZE = 6;
	vector<InventoryObject*> inventory_;
	InventoryObject* missionObject;
	Player* player_;
public:
	Inventory(Player* player);
	~Inventory();

	bool addObject(InventoryObject* iO);
	bool addMisionObject(InventoryObject* io);

	bool useObject(int indexObject);

	void removeObject(int indexObject);
	void removeMisionObject();

	void clearInventory();
	bool inventoryFull();

	void draw();
};

