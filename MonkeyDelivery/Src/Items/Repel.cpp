#include "Repel.h"
#include "../Logic/Game.h"
#include "../Player/Player.h"

Repel::Repel(Texture* tex, Game* game, Player* player) : InventoryObject(tex, game, player){
    isConsumable_ = true;
    setTypeObject(CONSUMABLES);
}

bool Repel::useObject(){
    player_->initPowerUp(repelente);
    sdlutils().soundEffects().at("soda").setVolume(game_->getSoundEfectsVolume() * game_->getGeneralVolume());
    sdlutils().soundEffects().at("soda").play(0, 1);
    return true;
}
