#include "Flashlight.h"
#include "Player.h"

Flashlight::Flashlight(Texture* tex) : active(false), InventoryObject(tex)
{
}

bool Flashlight::useObject() {
	if (!player_->isAsleep()) {
		if (!active) {
			cout << " Hola linternita";
			player_->changeFLState(true);
			player_->changeLState(false);
		}
		else {
			cout << "Adios linternita";
			player_->changeFLState(false);
			player_->setOrientation("off");
		}
		cout << endl;
		active = !active;
		return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
	}
}

void Flashlight::setActive(bool b)
{
	active = b;
}
