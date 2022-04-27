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
	overlay_ = game->getTexture(UI_InventoryBarOverlay);

	
	xObj = game->getWindowWidth() / 25;
	yObj = game->getWindowHeight() / 14;
	xInventory = game->getWindowWidth() / 2 - xObj * 7 / 2;
	yInventory = game->getWindowHeight() - game->getWindowHeight() / 10;

	baseRect_ = {xInventory, yInventory, xObj*7, yObj}; //hay que cambiarlo por window H/H	
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
		inventory_[0] =iO;
		break;
	case CONSUMABLES:
		if (inventory_[2] == nullptr) inventory_[2] = iO;		
		else inventory_[3] = iO;				
		break;
	case PICKAXE:
		 inventory_[4] = iO;
		break;
	case LANTERN:
		inventory_[1] = iO;
		break;
	case PACKAGE:
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

/// <summary>
/// Recorre el inventario en b�squeda de objetos que sean nullptr. Si no encuentra ninguno
/// devuelve true
/// </summary>
/// <returns>True si el inventario est� lleno</returns>
//bool Inventory::inventoryFull(){
//
//	if (inventory_.size() >= INVENTORY_SIZE) {	
//		int i = 0;
//		while (i < inventory_.size() && inventory_[i] != nullptr)
//			i++;
//		return i == inventory_.size();
//	}
//	return false;
//}

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
		SDL_Rect oRect = { xInventory + base_->getW() / 7 * 6 * 4, yObj , xObj,yObj };
		missionObject_->getTexture()->render(oRect);
	}
	int size = inventory_.size();
	
	for (int i = 0; i < INVENTORY_SIZE; i++) 
	{
		SDL_Rect oRect;
		if (i > 3) oRect = { xInventory + base_->getW() / 7 * (i+1) * 4, yInventory , xObj,yObj };		
		else oRect = { xInventory + base_->getW() / 7 * i * 4, yInventory , xObj, yObj };
		
		
		if (i < inventory_.size()&&inventory_[i]!=nullptr) 						
			inventory_[i]->getTexture()->render(oRect);
				
		if (i == selectedInventoryObject)
		{
			oRect.x += xObj / 9 * i;
			base_->render(oRect);
		}
			
		
	}
	overlay_->render(baseRect_);
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
