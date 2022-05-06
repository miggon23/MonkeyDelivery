
#include "Skates.h"
#include "../Player/Player.h"
#include "../Logic/Game.h"

Skates::Skates(Texture* tex, Game* game,Player* player) : speedMult(1.2), InventoryObject(tex, game,player){
	setTypeObject(BOOTS);
	active = false;
}

void Skates::setCorrectTexture(){
	setMyTexture(game_->getTexture(Item_Boots01));
}

bool Skates::useObject(){
	player_->initPowerUp(boots, speedMult);
	active = !active;
	return false;
}
