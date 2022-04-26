#include "EnergyDrink.h"
#include "../Logic/Game.h"
#include "../Player/Player.h"

EnergyDrink::EnergyDrink(Texture* tex,  Game* game,Player* player) : InventoryObject(tex, game,player){
    isConsumable_ = true;
    setTypeObject(CONSUMABLES);
}

bool EnergyDrink::useObject()
{
    /*player_->recoverEnergy(player_->getMaxEnergy() * energyBonus_);
    double newVel = player_->getVel();
    newVel *= speedBonus_;
    player_->setVel(newVel);
    player_->setBonusSpending(energyBonus_);*/
    std::cout << "energydrink activado: NO GASTA ENERGIA EL JUGADOR Y VA MAS RAPIDO" << std::endl;
    player_->initPowerUp(energyDrink);
    sdlutils().soundEffects().at("soda").setVolume(game_->getSoundEfectsVolume()*game_->getGeneralVolume());
    sdlutils().soundEffects().at("soda").play(0, 1);
    return true;
}