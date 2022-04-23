#pragma once

#include <vector>
#include "../View/Texture.h"

using namespace std;

class InventoryObject;
class Player;
class Game; 
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
	SDL_Rect baseRect_, overlayRect_;

	//OBJECTO SELECCIONADO
	int selectedInventoryObject;
	int selectedInventoryObjectLast;

public:
	Inventory(Game* game, Player* player, SDL_Renderer* renderer);
	~Inventory();

	bool addObject(InventoryObject* iO);
	bool addMisionObject(InventoryObject* io);

	bool useObject(int indexObject);

	void removeObject(int indexObject);
	void removeMisionObject();

	bool hasMissionObject();

	void clearInventory();
	//bool inventoryFull();
	bool inventoryFull(InventoryObject* x);
	void draw();

	void changeSelectedObject(int x);
	void selectObject(int index);
	void useSelectedObject();
};