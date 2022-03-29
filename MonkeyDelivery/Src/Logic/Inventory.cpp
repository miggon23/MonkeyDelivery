#include "Inventory.h"
#include "InventoryObject.h"
#include <iostream>
#include <SDL_rect.h>
#include "../View/Texture.h"

Inventory::Inventory(Player* player, SDL_Renderer* renderer) : player_(player)
{
	missionObject_ = nullptr;

	string route = "../Images/ui/inventorybar2.png";
	base_ = new Texture(renderer, route);
	route = "../Images/ui/inventorybar3.png";
	overlay_ = new Texture(renderer, route);
	baseRect_ = {650, 900, 120*4, 18*4};
}

Inventory::~Inventory()
{
	clearInventory();

	delete base_;
}

bool Inventory::addObject(InventoryObject* iO)
{
	//Comprobamos que el inventario no est� lleno
	if (inventoryFull())
		return false;
	
	//Se a�ade el objeto y se le asigna el player
	inventory_.push_back(iO);
	iO->attachPlayer(player_);

	return true;
}

/// <summary>
/// A�ade el paquete de entrega al slot reservado para ello en el inventario. Si ya tiene uno,
/// significa que a�n no ha terminado la misi�n por lo que el m�todo te dice si el jugador ha entregado el 
/// paquete o no. �til para no solapar misiones
/// </summary>
/// <param name="io">Paquete de entrega a a�adir en el inventario</param>
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
	//Si no hab�a que eliminarlo, no se hace nada
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
/// Recorre el inventario en b�squeda de objetos que sean nullptr. Si no encuentra ninguno
/// devuelve true
/// </summary>
/// <returns>True si el inventario est� lleno</returns>
bool Inventory::inventoryFull() {
	
	//int i = 0;
	//// error grave, saca elementos del vector
	//while (i < inventory_.size() && inventory_[i] != nullptr)
	//	i++;
	//return i == inventory_.size();
	// quer�is esto:
	return inventory_.size() == INVENTORY_SIZE;
}

void Inventory::draw() 
{
	base_->render(baseRect_);
															
	if (hasMissionObject()) { // si hay mission object, renderiza su textura
		missionObject_->getTexture()->render(baseRect_);
	}
	int size = inventory_.size();
	
	for (int i = 0; i < size; i++) 
	{
		if (i == 4) continue;
		SDL_Rect oRect = { 650 + base_->getW() / 7 * i * 4, 900 , 18 * 4, 18 * 4 }; // 790 = pos primer objeto 80 = separaci�n 
		inventory_[i]->getTexture()->render(oRect);
	}
	overlay_->render(baseRect_);
}