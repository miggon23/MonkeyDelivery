#include "Pickaxe.h"
#include "Player.h"
#include "Game.h"
#include <string>
Pickaxe::Pickaxe(Texture* tex, Game* game):InventoryObject(tex, game),uses_(0) {
	isConsumable_ = true;
	setTypeObject("Pickaxe");
}
bool Pickaxe::useObject(){
	
	SDL_Rect X = {player_->getX(), player_->getY(),player_->getWidth()+20,player_->getHeight()+20};
	std::cout << "xPickaxeCollider: " << player_->getX() << " yPickaxeCollider: " << player_->getY() << std::endl;
	std::cout << "widthPickaxeCollider: " << player_->getWidth() + 20 << " heightPickaxeCollider: " << player_->getHeight() + 20 << std::endl;
	//uses_++;
	//if(uses_>=3)return true;
	return false;
}


