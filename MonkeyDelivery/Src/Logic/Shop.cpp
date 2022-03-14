#include "Shop.h"
#include <iostream>
#include "InventoryObject.h"
#include "Inventory.h"
#include "Player.h"
#include "Bike.h"

Shop::Shop(Player* player)
{
	this->player = player;
}

Shop::~Shop()
{
	clearElements();
}

void Shop::actualice()
{
	clearElements();
	addElements(1);
}

void Shop::clearElements()
{
	for (auto e : objects)
	{
		delete e;
	}

	objects.clear();
}

void Shop::addElements(int level)
{
	switch (level)
	{
	case 1:
		objects.push_back(new Bike());
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		std::cout << "nivel de tienda no valido" << endl;
		break;
	}
}

bool Shop::buyObject(int id, int price)
{
	if (id < objects.size() && player->inventoryFull() && player->moneyChange(price))
	{		
		player->addObjectToInventory(objects[id]);
		objects.erase(objects.begin() + id);

		return true;
	}
	else return false; 
	
}
