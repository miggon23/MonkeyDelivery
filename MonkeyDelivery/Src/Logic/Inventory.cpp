#include "Inventory.h"
#include "InventoryObject.h"
#include "game.h"
#include <iostream>
#include <SDL_rect.h>
#include "../View/Texture.h"
#include <string>

Inventory::Inventory(Game* game, Player* player, SDL_Renderer* renderer) : player_(player), selectedInventoryObjectLast(0), selectedInventoryObject(0),overlayRect_(){
	missionObject_ = nullptr;

	base_ = game->getTexture(UI_InventoryBar);
	selector_ = game->getTexture(UI_InventorySelector);
	overlay_ = game->getTexture(UI_InventoryBarOverlay);
	baseRect_ = {650, 900, 120*4, 18*4}; //hay que cambiarlo por window H/H	
	InventoryObject* relleno = new InventoryObject(game->getTexture(UI_Black), game, game->getPlayer());
	//Inicializar InventoryObjects
	for (int i = 0; i < INVENTORY_SIZE+1; i++){
		inventory_.push_back(relleno);
		inventory_[i] = nullptr;
	}
	delete relleno;
	relleno = nullptr;
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
	TypeObjectInventory aux = iO->getTypeObject();
	switch (aux) {
	case BOOTS:
		removeObject(inventory_[0]);
		inventory_[0] =iO;
		break;
	case CONSUMABLES:
		if (inventory_[2] == nullptr) inventory_[2] = iO;		
		else { 
			removeObject(inventory_[3]);
			inventory_[3] = iO; }
		break;
	case PICKAXE:
		removeObject(inventory_[4]);
		inventory_[4] = iO;
		break;
	case LANTERN:
		removeObject(inventory_[1]);
		inventory_[1] = iO;
		break;
	case PACKAGE:
		removeObject(inventory_[5]);
		inventory_[5] = iO;
		break;
	default:
		return false;
		break;
	}
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

bool Inventory::inventoryFull(InventoryObject* x){
	TypeObjectInventory aux =x->getTypeObject();
	switch (aux){
	case BOOTS:
		//return inventory_[0] != nullptr;
		return false;
		break;
	case CONSUMABLES:
		return inventory_[2] != nullptr&& inventory_[3] != nullptr;;
		break;
	case PICKAXE:
		//return inventory_[4] != nullptr;
		return false;
		break;
	case LANTERN:
		//return inventory_[1] != nullptr;
		return false;
		break;
	case PACKAGE:
		return inventory_[5] != nullptr;
		break;
	default:
		return true;
		break;
	}
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
			selector_->render(oRect);
		
	}
	overlay_->render(baseRect_);
}

void Inventory::removeObject(InventoryObject* x){
	if (x != nullptr) {
		delete x;
		x = nullptr;
	}
}

void Inventory::changeSelectedObject(int x){
	if (selectedInventoryObject < inventory_.size() && inventory_[selectedInventoryObject] != nullptr &&inventory_[selectedInventoryObject]->getActive()) { useSelectedObject(); };
	selectedInventoryObject += x;
	selectedInventoryObject %= INVENTORY_SIZE;
	//std::cout << selectedInventoryObject << std::endl;
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

void Inventory::desactivateUseSelectedObject(){	
	if (selectedInventoryObject < inventory_.size() && inventory_[selectedInventoryObject] != nullptr && inventory_[selectedInventoryObject]->getActive()) { useSelectedObject(); };	
}
