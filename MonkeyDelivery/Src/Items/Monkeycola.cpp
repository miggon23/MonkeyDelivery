#include "Monkeycola.h"
#include "../Logic/Game.h"
#include "../Player/Player.h"

Monkeycola::Monkeycola(Texture* tex, Game* game, Player* player) : InventoryObject(tex, game, player)
{
	isConsumable_ = true;
	setTypeObject(CONSUMABLES);
}

bool Monkeycola::useObject()
{
	player_->initPowerUp(monkeycola);
	sdlutils().soundEffects().at("soda").setVolume(game_->getSoundEfectsVolume() * game_->getGeneralVolume());
	sdlutils().soundEffects().at("soda").play(0, 1);
	return true;
}
