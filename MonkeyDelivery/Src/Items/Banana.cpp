#include "Banana.h"
#include "../Logic/Game.h"
#include "../Player/Player.h"

Banana::Banana(Texture* tex, Game* game, Player* player) : InventoryObject(tex, game, player)
{
	isConsumable_ = true;
	setTypeObject(CONSUMABLES);
}

bool Banana::useObject()
{
	player_->initPowerUp(banana);
	sdlutils().soundEffects().at("soda").setVolume((int)(game_->getSoundEfectsVolume() * game_->getGeneralVolume()));
	sdlutils().soundEffects().at("soda").play(0, 1);
	return true;
}
