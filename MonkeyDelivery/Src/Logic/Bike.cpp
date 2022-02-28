#include "Bike.h"
#include "Player.h"

Bike::Bike() : active(false), speedMult(2.5)
{
}

bool Bike::useObject() {
	if (!active) {
		player_->setVelX(player_->getVelX() * speedMult);
		player_->setVelY(player_->getVelY() * speedMult);
		cout << "Montando en Bici";
	}
	else {
		player_->setVelX(player_->getVelX() / speedMult);
		player_->setVelY(player_->getVelY() / speedMult);
		cout << "Me bajo de la Bici";
	}
	cout << endl;
	active = !active;
	return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
}
