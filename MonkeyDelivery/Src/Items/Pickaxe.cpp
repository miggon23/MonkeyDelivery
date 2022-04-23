#include "Pickaxe.h"
#include "../Player/Player.h"
#include "../Logic/Game.h"
#include "Rock.h"
#include <string>

Pickaxe::Pickaxe(Texture* tex, Game* game,int level,Player* player):InventoryObject(tex, game,player) {
	isConsumable_ = true;
	level_ = level % 2;
	/*if (level_ == 1)tex = game_->getTexture();
	else tex = game->getTexture();*/

	setTypeObject(PICKAXE);
}
bool Pickaxe::useObject(){
	
	SDL_Rect rect = {player_->getX(), player_->getY(),player_->getWidth()+20,player_->getHeight()+20};
	std::cout << "xPickaxeCollider: " << player_->getX() << " yPickaxeCollider: " << player_->getY() << std::endl;
	std::cout << "widthPickaxeCollider: " << player_->getWidth() + 20 << " heightPickaxeCollider: " << player_->getHeight() + 20 << std::endl;
	for (auto x:game_->getGameObjects()){
		Rock* possibleRock = dynamic_cast<Rock*>(x);//Cacheao para ver si es una roca o no
		if (possibleRock!=nullptr &&possibleRock->collide(rect)&&possibleRock->seeLevelToDestroy()<=level_) {
			game_->removeGameObject(x);			
		}		
	}
	return false;
}