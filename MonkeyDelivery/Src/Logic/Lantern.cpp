#include "Lantern.h"
#include "Player.h"
#include "Flashlight.h"
#include "Game.h"

Lantern::Lantern(Texture* tex, Game* game) : InventoryObject(tex, game)
{
	active = false;
}

bool Lantern::useObject() {
	if (!player_->isAsleep()) {
		if (!active) {
			cout << " Hola linternita circular";
			player_->changeLState(true);
			player_->changeFLState(false);
			sdlutils().soundEffects().at("lantern").setVolume(game_->getSoundEfectsVolume());
			sdlutils().soundEffects().at("lantern").play(0, 1);

			//Flashlight::setActive(false);
		}
		else {
			cout << "Adios linternita circular";
			player_->changeLState(false);
			player_->setOrientation("off");
			sdlutils().soundEffects().at("lantern").setVolume(game_->getSoundEfectsVolume());
			sdlutils().soundEffects().at("lantern").play(0, 1);

		}
		cout << endl;
		active = !active;
		return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
	}
}