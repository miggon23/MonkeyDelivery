
#include "Skates.h"
#include "Player.h"

Skates::Skates(Texture* tex) : active(false), speedMult(1.8), InventoryObject(tex){
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
	cout << endl;
	auto c = player_->getVel();
	active = !active;
	return false;
}
