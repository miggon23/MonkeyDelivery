#include "Inventory.h"
#include "InventoryObject.h"
#include "game.h"
#include <iostream>
#include <SDL_rect.h>
#include "../View/Texture.h"
#include <string>

Inventory::Inventory(Game* game, Player* player, SDL_Renderer* renderer) : player_(player), selectedInventoryObjectLast(0), selectedInventoryObject(0){
	missionObject_ = nullptr;

	base_ = game->getTexture(UI_InventoryBar);
	overlay_ = game->getTexture(UI_InventoryBarOverlay);
	baseRect_ = {650, 900, 120*4, 18*4}; //hay que cambiarlo por window H/H
}

Inventory::~Inventory()
{
	clearInventory();
	delete missionObject_;	

	//no se pueden eliminar estas texturas
	//delete base_;
	//delete overlay_;


	base_ = nullptr;
	overlay_ = nullptr;
}

bool Inventory::addObject(InventoryObject* iO){
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
	//objeto sleccionado del inventario
	//selectedInventoryObject = indexObject;

	//Devuelve false si el objeto no pudo ser utilizado
	if (indexObject >= inventory_.size())
		return false;
	//Si el objeto es de un solo uso (useObject() devuelve true)
	//Lo eliminamos
	//Si no hab�a que eliminarlo, no se hace nada
	if (inventory_[indexObject]!=nullptr&&inventory_[indexObject]->useObject()) //useObject() devuelve un booleano!!
	{
		removeObject(indexObject);
	}
	else selectedInventoryObjectLast = indexObject;

	return true;
}

void Inventory::removeObject(int indexObject)
{
	delete inventory_[indexObject];
	inventory_[indexObject] = nullptr; 
	//inventory_.erase(inventory_.begin() + indexObject);
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
bool Inventory::inventoryFull(){	
	if (inventory_.size() >= INVENTORY_SIZE) {	
		int i = 0;
		while (i < inventory_.size() && inventory_[i] != nullptr)
			i++;
		return i == inventory_.size();
	}
	// quer�is esto:
	return false;
}

void Inventory::draw() 
{
	base_->render(baseRect_);
	
															
	if (hasMissionObject()) { // si hay mission object, renderiza su textura
		SDL_Rect oRect = { 650 + base_->getW() / 7 * 6 * 4, 900 , 18 * 4, 18 * 4 };
		missionObject_->getTexture()->render(oRect);
	}
	int size = inventory_.size();
	
	for (int i = 0; i < INVENTORY_SIZE; i++) 
	{
		SDL_Rect oRect;
		if (i > 3) oRect = { 650 + base_->getW() / 7 * (i+1) * 4, 900 , 18 * 4, 18 * 4 };		
		else oRect = { 650 + base_->getW() / 7 * i * 4, 900 , 18 * 4, 18 * 4 };
		
		
		if (i < inventory_.size()&&inventory_[i]!=nullptr) 						
			inventory_[i]->getTexture()->render(oRect);
				
		if (i == selectedInventoryObject) 
			base_->render(oRect);
		
	}
	overlay_->render(baseRect_);
}

//TEMPORAL
string Inventory::activeObject(){
	if (selectedInventoryObject >= inventory_.size()) {
		return "NoActiveInventoryItem";
	}
	// return inventory_[selectedInventoryObject]->getTypeObject();
}

void Inventory::changeSelectedObject(int x){
	if (selectedInventoryObject < inventory_.size() && inventory_[selectedInventoryObject] != nullptr &&inventory_[selectedInventoryObject]->getActive()) { useSelectedObject(); };
	selectedInventoryObject += x;
	selectedInventoryObject %= INVENTORY_SIZE;

	if (selectedInventoryObject < 0)selectedInventoryObject = INVENTORY_SIZE-1;
	
}

void Inventory::selectObject(int index){	
	if ( selectedInventoryObject<inventory_.size()&& inventory_[selectedInventoryObject] != nullptr &&inventory_[selectedInventoryObject]->getActive()) { useSelectedObject(); };
	//selectedInventoryObject = index % inventory_.size();
	selectedInventoryObject = index % INVENTORY_SIZE;
}

void Inventory::useSelectedObject(){
	useObject(selectedInventoryObject);
}
