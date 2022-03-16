#include "EnergyDrink.h"
#include "Game.h"
#include "Player.h"

bool EnergyDrink::useObject()
{
    player_->recoverEnergy(player_->getMaxEnergy() * 1.2); // aumenta 20%
    double newVel = player_->getVel();
    newVel *= 1.15; // aumenta 15 %
    player_->setVel(newVel);
    // en 15 seg. ->
    player_->resetVelocity();
    return true;
}
