#include "Pickaxe.h"

Pickaxe::Pickaxe(Texture* tex):InventoryObject(tex),uses_(3) {
	isConsumable_ = true;
}
bool Pickaxe::useObject(){

	if(uses_>=3)return true;
	return false;
}


