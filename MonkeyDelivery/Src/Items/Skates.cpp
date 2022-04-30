
#include "Skates.h"
#include "../Player/Player.h"
#include "../Logic/Game.h"

Skates::Skates(Texture* tex, Game* game,Player* player) : speedMult(1.8), InventoryObject(tex, game,player){
	setTypeObject(BOOTS);
	active = false;
}

void Skates::setCorrectTexture(){
	setMyTexture(game_->getTexture(Item_Boots02));
}

bool Skates::useObject()
{
	if (!active) {
		player_->setVel(player_->getVel() * speedMult);
		cout << "Patines";
	}
	else {
		player_->setVel(player_->getVel() / speedMult);
		cout << "Me quito los patines";
	}
	player_->initPowerUp(boots);
	cout << endl;
	auto c = player_->getVel();
	active = !active;
	return false;
}
