#include "Bike.h"
#include "../Player/Player.h"

Bike::Bike(Texture* tex, Game* game,Player* player) : speedMult(2.5), InventoryObject(tex, game,player)
{
	active = false;
	setTypeObject(BOOTS);
}

bool Bike::useObject() {
	if ( !active ) {
		player_->setVel(player_->getVel() * speedMult);
		cout << "Montando en Bici";

	}
	else {
		player_->setVel(player_->getVel() / speedMult);
		cout << "Me bajo de la Bici";
	}
	cout << endl;
	auto c = player_->getVel();
	active = !active;
	return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
}
