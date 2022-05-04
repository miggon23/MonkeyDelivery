
#include "Skates.h"
#include "../Player/Player.h"
#include "../Logic/Game.h"

Skates::Skates(Texture* tex, Game* game,Player* player) : speedMult(1.2), InventoryObject(tex, game,player){
	setTypeObject(BOOTS);
	active = false;
}

void Skates::setCorrectTexture(){
	setMyTexture(game_->getTexture(Item_Boots02));
}

bool Skates::useObject()
{
	/*if (!active) {
		player_->setVel(player_->getVel() * speedMult);
	}
	else {
		player_->setVel(player_->getVel() / speedMult);
	}*/
	player_->initPowerUp(boots);
	//active = !active;
	return false;
}
