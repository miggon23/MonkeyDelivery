#include "Shop.h"
#include <iostream>
#include "InventoryObject.h"
#include "Inventory.h"
#include "../Player/Player.h"
#include "../Items/Bike.h"
#include "../Items/EnergyDrink.h"
#include "../Items/Skates.h"
#include "../Items/Flashlight.h"
#include "../Items/Lantern.h"
#include "../Items/Banana.h"
#include "../Items/Repel.h"
#include "../Items/Monkeycola.h"
#include "Game.h"

Shop::Shop(Player* player, Game* game)
{
	this->player = player;
	this->game = game;
}

Shop::~Shop()
{
	clearElements();
	game = nullptr;
	player = nullptr;
}

void Shop::actualice(int level){
	
	clearElements();
	addElements(level);
}

void Shop::clearElements()
{
	if (objects.size() > 0)
	{
		for (auto e : objects)
		{
			if (e.inventoryObject != nullptr)
				delete e.inventoryObject;
			//objects2.erase(objects2.begin());
		}
		objects.clear();
	}
	
}

void Shop::addElements(int level)
{
	switch (level)
	{
	case 1:
		objects.push_back({ new EnergyDrink(game->getTexture(shop_Soda), game,game->getPlayer()), 0, 0, 3, 20 });
		objects.push_back({ new Bike(game->getTexture(shop_Boots01), game,game->getPlayer()), 1, 0, 1, 30});
		objects.push_back({ new Banana(game->getTexture(shop_Banana), game,game->getPlayer()), 1, 0, 1, 20 });
		objects.push_back({ new Flashlight(game->getTexture(shop_Boots02), game,game->getPlayer()), 3, 0, 1, 10});
		break;
	case 2:
		objects.push_back({ new EnergyDrink(game->getTexture(shop_Soda), game,game->getPlayer()), 0, 0, 3, 20 });
		objects.push_back({ new Skates(game->getTexture(shop_Boots02), game,game->getPlayer()), 2, 0, 1, 25 });		
		objects.push_back({ new Banana(game->getTexture(shop_Banana), game,game->getPlayer()), 1, 0, 1, 20 });
		objects.push_back({ new Repel(game->getTexture(Item_Spray), game,game->getPlayer()), 0, 0, 3, 40 });
		break;
	case 3:
		objects.push_back({ new Repel(game->getTexture(Item_Spray), game,game->getPlayer()), 0, 0, 3, 40 });
		objects.push_back({ new EnergyDrink(game->getTexture(shop_Soda), game,game->getPlayer()), 0, 0, 3, 20 });
		objects.push_back({ new Banana(game->getTexture(shop_Banana), game,game->getPlayer()), 1, 0, 1, 20 });
		objects.push_back({ new Lantern(game->getTexture(Item_Lantern01), game,game->getPlayer()), 0, 0, 1, 10 });
		break;
	default:
		std::cout << "nivel de tienda no valido" << endl;
		break;
	}
}

bool Shop::buyObject(int id, int price)
{
	if (id < objects.size() && objects[id].stock>0 &&!player->inventoryFull(objects[id].inventoryObject) && player->moneyChange(-price)){		
		
		if (objects[id].inventoryObject->getTypeObject() != CONSUMABLES) { 
			objects[id].inventoryObject->setCorrectTexture();
			player->addObjectToInventory(objects[id].inventoryObject); 
			objects[id].inventoryObject = nullptr;
		}
		else CreateNewObject(objects[id].inventoryObject);
		objects[id].stock--;
		
		return true;
	}
	else return false; 	
}

bool Shop::inventoryFull(int selected)
{
	return player->inventoryFull(objects[selected].inventoryObject);
}

void Shop::CreateNewObject(InventoryObject* O){
	//NOTA: NECESITO MIRAR QUE CLASE DE OBJECTO CONSUMIBLE ES PARA PODER DUPLICARLO
	Banana* possible = dynamic_cast<Banana*>(O);
	if (possible != nullptr) { player->addObjectToInventory(new Banana(game->getTexture(Item_Banana), game, player)); return; }
	possible = nullptr;

	EnergyDrink* possible2 = dynamic_cast<EnergyDrink*>(O);
	if (possible2 != nullptr) { player->addObjectToInventory(new Banana(game->getTexture(Item_Soda02), game, player)); return; }
	possible2 = nullptr;

	Monkeycola* possible3 = dynamic_cast<Monkeycola*>(O);
	if (possible2 != nullptr) { player->addObjectToInventory(new Banana(game->getTexture(Item_Soda01), game, player)); return; }
	possible3 = nullptr;

	Repel* possible4 = dynamic_cast<Repel*>(O);
	if (possible2 != nullptr) { player->addObjectToInventory(new Banana(game->getTexture(Item_Spray), game, player)); return; }
}

