#include "Bike.h"
#include "../Player/Player.h"
#include "../Logic/Game.h"
Bike::Bike(Texture* tex, Game* game,Player* player) : speedMult(1.6), InventoryObject(tex, game,player)
{
	active = false;
	setTypeObject(BOOTS);
}

bool Bike::useObject() {
	
	player_->initPowerUp(boots, speedMult);
	//player_->setIsWearingBoots(true);
	return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
}

void Bike::setCorrectTexture(){
	setMyTexture(game_->getTexture(Item_Boots02));
}
