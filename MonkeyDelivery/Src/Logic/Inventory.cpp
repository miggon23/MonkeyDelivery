#include "Inventory.h"
#include "InventoryObject.h"
#include <iostream>

Inventory::Inventory(Game* game, Player* player) : game_(game), player_(player)
{
	inventory_.resize(INVENTORY_SIZE);
	for (int i = 0; i < inventory_.size(); i++) {
		inventory_[i] = nullptr;
	}
	missionObject = nullptr;
}

Inventory::~Inventory()
{
	clearInventory();
}

bool Inventory::addObject(InventoryObject* iO)
{
	//Comprobamos que el inventario no esté lleno
	if (inventoryFull())
		return false;
	int i = 0;

	//Se posiciona en el primer espacio de inventario que está vacío
	while (inventory_[i] != nullptr)
		i++;

	//Se añade el objeto y se le asigna el player
	inventory_[i] = iO;
	inventory_[i]->attachPlayer(player_);
}

/// <summary>
/// Añade el paquete de entrega al slot reservado para ello en el inentario. Si ya tiene uno,
/// significa que aún no ha terminado la misión por lo que el método te dice si el jugador ha entregado el 
/// paquete o no. Útil para no solapar misiones
/// </summary>
/// <param name="io">Paquete de entrega a añadir en el inventario</param>
/// <returns></returns>
bool Inventory::addMisionObject(InventoryObject* io)
{
	if (missionObject == nullptr)
	{
		missionObject = io;
		return true;
	}
	else
		return false;
}

void Inventory::useObject(int indexObject)
{
	// queréis devolver si más?
	if (inventory_[indexObject] == nullptr)
		return;
	//Si el objeto es de un solo uso (useObject() devuelve true)
	//Lo eliminamos
	//Si no había que eliminarlo, no se hace nada
	if (inventory_[indexObject]->useObject()) //useObject() devuelve un booleano!!
	{
		removeObject(indexObject);
	}
}

void Inventory::removeObject(int indexObject)
{
	delete inventory_[indexObject];
	inventory_[indexObject] = nullptr;
}

void Inventory::removeMisionObject()
{
	delete missionObject;
	missionObject = nullptr;
}


void Inventory::clearInventory()
{
	// iteradores
	for (auto gO : inventory_) {
		delete gO;
	}

	if (missionObject != nullptr) {
		delete missionObject;
		missionObject = nullptr;
	}
}

/// <summary>
/// Recorre el inventario en búsqueda de objetos que sean nullptr. Si no encuentra ninguno
/// devuelve true
/// </summary>
/// <returns>True si el inventario está lleno</returns>
bool Inventory::inventoryFull() {
	
	int i = 0;
	// error grave, saca elementos del vector
	while (i < inventory_.size() && inventory_[i] != nullptr)
		i++;
	return i == inventory_.size();
	// queréis esto:
	//return inventory_.size() == inventory_.INVENTORY_SIZE;
}


