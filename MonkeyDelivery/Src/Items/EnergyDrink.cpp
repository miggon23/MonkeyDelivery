#include "EnergyDrink.h"
#include "../Logic/Game.h"
#include "../Player/Player.h"

EnergyDrink::EnergyDrink(Texture* tex,  Game* game,Player* player) : InventoryObject(tex, game,player)
{
    isConsumable_ = true;
    setTypeObject(CONSUMABLES);
}

bool EnergyDrink::useObject()
{
    player_->recoverEnergy(player_->getMaxEnergy() * energyBonus_);
    double newVel = player_->getVel();
    newVel *= speedBonus_;
    player_->setVel(newVel);
    sdlutils().soundEffects().at("soda").setVolume(game_->getSoundEfectsVolume()*game_->getGeneralVolume());
    sdlutils().soundEffects().at("soda").play(0, 1);
    // en 15 seg. ->
    player_->resetVelocity();
    return true;
}