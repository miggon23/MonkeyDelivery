#include "Shop.h"
#include <iostream>
#include "InventoryObject.h"
#include "Inventory.h"
#include "Player.h"
#include "Bike.h"
#include "EnergyDrink.h"
#include "Skates.h"
#include "Flashlight.h"
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
		if(e.inventoryObject != nullptr)
			delete e.inventoryObject;
		//objects2.erase(objects2.begin());
	}
	objects.clear();
}

void Shop::addElements(int level)
{
	switch (level)
	{
	case 1:
		
		objects.push_back({ new EnergyDrink(game->getTexture(drinkTexture)),0,0,1,1000}); //<-- ahora los objetos llevan textura en la constructora para que puedan ser renderizados por el inventario
		objects.push_back({ new Bike(game->getTexture(bikeTexture)),1,0,1,1000});
		objects.push_back({ new Skates(game->getTexture(skatesTexture)),2,0,1,1000});		
		objects.push_back({ new Flashlight(game->getTexture(linternaProvi)),3,0,1,1000});
		objects.push_back({ new Bike(game->getTexture(bullTexture)),0,105,1,1000});
		objects.push_back({ new Bike(game->getTexture(bullTexture)),1,105,1,1000});
		objects.push_back({ new Bike(game->getTexture(bullTexture)),2,105,1,1000});
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
	if (id < objects.size() && objects[id].stock>0 &&!player->inventoryFull() && player->moneyChange(-price)){	
		player->addObjectToInventory(objects[id].inventoryObject);		
		objects[id].inventoryObject = nullptr;
		objects[id].stock--;		
		return true;
	}
	else return false; 	
}

bool Shop::inventoryFull()
{
	return player->inventoryFull();
}
