#include "EnergyDrink.h"
#include "../Logic/Game.h"
#include "../Player/Player.h"

EnergyDrink::EnergyDrink(Texture* tex,  Game* game,Player* player) : InventoryObject(tex, game,player){
    isConsumable_ = true;
    setTypeObject(CONSUMABLES);
}

void EnergyDrink::setCorrectTexture(){
    setMyTexture(game_->getTexture(Item_Soda02));
}

bool EnergyDrink::useObject()
{
    
    player_->initPowerUp(energyDrink);
    sdlutils().soundEffects().at("soda").setVolume((int)(game_->getSoundEfectsVolume()*game_->getGeneralVolume()));
    sdlutils().soundEffects().at("soda").play(0, 1);
    return true;
}