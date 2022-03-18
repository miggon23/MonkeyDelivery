#include "Shop.h"
#include <iostream>
#include "InventoryObject.h"
#include "Inventory.h"
#include "Player.h"
#include "Bike.h"
#include "Game.h"

Shop::Shop(Player* player, Game* game)
{
	this->player = player;
	this->game = game;
}

Shop::~Shop()
{
	clearElements();
	player = nullptr;
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
		objects.push_back(new Bike(game->getTexture(bullTexture))); //<-- ahora los objetos llevan textura en la constructora para que puedan ser renderizados por el inventario
		objects.push_back(new Bike(game->getTexture(bullTexture)));
		objects.push_back(new Bike(game->getTexture(bullTexture)));
		objects.push_back(new Bike(game->getTexture(bullTexture)));
		objects.push_back(new Bike(game->getTexture(bullTexture)));
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
	if (id < objects.size() && !player->inventoryFull() && player->moneyChange(price))
	{		
		player->addObjectToInventory(objects[id]);
		objects.erase(objects.begin() + id);

		return true;
	}
	else return false; 
	
}
