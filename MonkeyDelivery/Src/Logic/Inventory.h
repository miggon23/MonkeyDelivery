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
	SDL_Rect baseRect_;
	SDL_Rect missionObjectRect_;

	//OBJECTO SELECCIONADO
	int selectedInventoryObject;
	int selectedInventoryObjectLast;

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

	
	string activeObject();
	void changeSelectedObject(int x);
	void selectObject(int index);
	void useSelectedObject();
};