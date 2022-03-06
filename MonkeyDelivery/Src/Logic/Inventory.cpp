#include "Inventory.h"
#include "InventoryObject.h"
#include <iostream>
#include <SDL_rect.h>
#include "../View/Texture.h"

Inventory::Inventory(Player* player, SDL_Renderer* renderer) : player_(player)
{
	missionObject_ = nullptr;

	string route = "../Images/ui/inventorybar.png";
	base_ = new Texture(renderer, route);
	baseRect_ = {250, 350, 300, 300/6};
}

Inventory::~Inventory()
{
	clearInventory();

	delete base_;
}

bool Inventory::addObject(InventoryObject* iO)
{
	//Comprobamos que el inventario no esté lleno
	if (inventoryFull())
		return false;
	
	//Se añade el objeto y se le asigna el player
	inventory_.push_back(iO);
	iO->attachPlayer(player_);

	return true;
}

/// <summary>
/// Añade el paquete de entrega al slot reservado para ello en el inventario. Si ya tiene uno,
/// significa que aún no ha terminado la misión por lo que el método te dice si el jugador ha entregado el 
/// paquete o no. Útil para no solapar misiones
/// </summary>
/// <param name="io">Paquete de entrega a añadir en el inventario</param>
/// <returns></returns>
bool Inventory::addMisionObject(InventoryObject* io)
{
	if (missionObject_ == nullptr)
	{
		missionObject_ = io;
		return true;
	}
	else
		return false;
}

bool Inventory::useObject(int indexObject)
{
	//Devuelve false si el objeto no pudo ser utilizado
	if (indexObject >= inventory_.size())
		return false;
	//Si el objeto es de un solo uso (useObject() devuelve true)
	//Lo eliminamos
	//Si no había que eliminarlo, no se hace nada
	if (inventory_[indexObject]->useObject()) //useObject() devuelve un booleano!!
	{
		removeObject(indexObject);
	}
	return true;
}

void Inventory::removeObject(int indexObject)
{
	delete inventory_[indexObject];
	inventory_.erase(inventory_.begin() + indexObject);
}

void Inventory::removeMisionObject()
{
	if (missionObject_ != nullptr) {
		delete missionObject_;
		missionObject_ = nullptr;
	}
}

bool Inventory::hasMissionObject()
{
	return missionObject_ != nullptr;
}


void Inventory::clearInventory()
{
	// iteradores
	for (auto gO : inventory_) {
		delete gO;
	}

	removeMisionObject();
}

/// <summary>
/// Recorre el inventario en búsqueda de objetos que sean nullptr. Si no encuentra ninguno
/// devuelve true
/// </summary>
/// <returns>True si el inventario está lleno</returns>
bool Inventory::inventoryFull() {
	
	//int i = 0;
	//// error grave, saca elementos del vector
	//while (i < inventory_.size() && inventory_[i] != nullptr)
	//	i++;
	//return i == inventory_.size();
	// queréis esto:
	return inventory_.size() == INVENTORY_SIZE;
}

void Inventory::draw() {
	base_->render(baseRect_);
}




