#include "Bike.h"
#include "Player.h"

Bike::Bike(Game* game) : speedMult(1.2), active(false), InventoryObject(game)
{
}

Bike::~Bike() {

}

bool Bike::useObject() {
	if (!active) {
		player_->setVelX(player_->getVelX() * speedMult);
		cout << "Montando en Bici";
	}
	else {
		player_->setVelY(player_->getVelY() / speedMult);
		cout << "Me bajo de la Bici";
	}
	cout << endl;
	active = !active;
	return false; //devolvemos false indicando que el objeto no deve destruirse tras usarlo
}