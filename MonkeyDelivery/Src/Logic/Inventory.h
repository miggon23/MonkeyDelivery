#pragma once

#include <vector>

using namespace std;

class InventoryObject;

class Inventory
{
private:
	const int INVENTORY_SIZE = 6;
	vector<InventoryObject*> inventory_;
	InventoryObject* missionObject;
public:
	Inventory();
	~Inventory();

	bool addObject(InventoryObject* iO);
	bool addMisionObject(InventoryObject* io);

	void useObject(int indexObject);

	void removeObject(int indexObject);
	void removeMisionObject();

	void clearInventory();
	bool inventoryFull();
};

