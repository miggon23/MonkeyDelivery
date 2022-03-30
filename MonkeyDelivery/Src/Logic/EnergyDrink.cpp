#include "EnergyDrink.h"
#include "Game.h"
#include "Player.h"

EnergyDrink::EnergyDrink(Texture* tex) : InventoryObject(tex)
{
    isConsumable_ = true;
}

bool EnergyDrink::useObject()
{
    player_->recoverEnergy(player_->getMaxEnergy() * energyBonus_);
    double newVel = player_->getVel();
    newVel *= speedBonus_;
    player_->setVel(newVel);
    sdlutils().soundEffects().at("soda").setVolume(game_->getSoundEfectsVolume());
    sdlutils().soundEffects().at("soda").play(0, 1);
    // en 15 seg. ->
    player_->resetVelocity();
    return true;

}
