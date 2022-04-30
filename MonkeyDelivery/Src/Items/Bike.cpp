#include "Bike.h"
#include "../Player/Player.h"
#include "../Logic/Game.h"
Bike::Bike(Texture* tex, Game* game,Player* player) : speedMult(2.5), InventoryObject(tex, game,player)
{
	active = false;
	setTypeObject(BOOTS);
}

bool Bike::useObject() {
	if ( !active ) {
		player_->setVel(player_->getVel() * speedMult);
	}
	else {
		player_->setVel(player_->getVel() / speedMult);
	}
	player_->initPowerUp(boots);
	auto c = player_->getVel();
	active = !active;
	return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
}

void Bike::setCorrectTexture(){
	setMyTexture(game_->getTexture(Item_Boots02));
}
