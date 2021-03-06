#include "Flashlight.h"
#include "../Player/Player.h"
#include "../Logic/Game.h"


Flashlight::Flashlight(Texture* tex, Game* game,Player* player) : InventoryObject(tex, game,player)
{
	active = false;
	setTypeObject(LANTERN);
}

void Flashlight::setCorrectTexture(){
	setMyTexture(game_->getTexture(Item_Lantern01));
}

bool Flashlight::useObject() {
	if (!player_->isAsleep()) {
		if (!active) {
			cout << " Hola linternita";
			player_->changeFLState(true);
			player_->changeLState(false);
			sdlutils().soundEffects().at("lantern").setVolume((int)(game_->getSoundEfectsVolume() * game_->getGeneralVolume()));
			sdlutils().soundEffects().at("lantern").play(0, 1);

		}
		else {
			cout << "Adios linternita";
			player_->changeFLState(false);
			player_->setOrientation("off");
			sdlutils().soundEffects().at("lantern").setVolume((int)(game_->getSoundEfectsVolume() * game_->getGeneralVolume()));
			sdlutils().soundEffects().at("lantern").play(0, 1);

		}
		cout << endl;
		active = !active;
	}
	return false;//devolvemos false indicando que el objeto no debe destruirse tras ser usado
}

void Flashlight::setActive(bool b)
{
	active = b;
}
