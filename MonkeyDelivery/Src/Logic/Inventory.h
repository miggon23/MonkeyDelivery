#pragma once

#include <vector>
#include "../View/Texture.h"

using namespace std;

class InventoryObject;
class Player;

class Inventory
{
private:
	const int INVENTORY_SIZE = 6;
	vector<InventoryObject*> inventory_;
	InventoryObject* missionObject_;
	Player* player_;

	//Renderizado
	Texture* base_;
	Texture* overlay_;
	SDL_Rect baseRect_;

public:
	Inventory(Player* player, SDL_Renderer* renderer);
	~Inventory();

	bool addObject(InventoryObject* iO);
	bool addMisionObject(InventoryObject* io);

	bool useObject(int indexObject);

	void removeObject(int indexObject);
	void removeMisionObject();

	bool hasMissionObject();

	void clearInventory();
	bool inventoryFull();

	void draw();
};

