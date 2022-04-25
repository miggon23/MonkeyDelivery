#include "PowerUpsManager.h"
#include "Game.h"
#include "../Player/Player.h"
#include "../sdlutils/VirtualTimer.h"
PowerUpsManager::PowerUpsManager(Game* game, Player* player):game_(game),player_(player),activatedEnergyDrink_(false),activateBoots(false),timerEnergyDrink_(new VirtualTimer()){
	//timerEnergyDrink_->pause();
}

PowerUpsManager::~PowerUpsManager(){
	player_ = nullptr;
	game_ = nullptr;
	delete timerEnergyDrink_;
	timerEnergyDrink_ = nullptr;
}

void PowerUpsManager::update(){
	if (activatedEnergyDrink_) {

		//Mostrar el ICONO 

		if (timerEnergyDrink_->currTime() >= timeEnergyDrinkLimit_) {
			player_->resetVelocity();
			player_->setStopSpending(false);
			activatedEnergyDrink_ = false;
			timerEnergyDrink_->pause();
			std::cout << "energydrink desactivado" << std::endl;
		}
	}
	if (activateBoots) {

		//MOSTAR EL ICONO
	}
}
void PowerUpsManager::InitTimer(PowerUps x){
	switch (x){
	case energyDrink:
		activatedEnergyDrink_ = true;
		timerEnergyDrink_->reset();
		break;
	default:
		break;
	}
}
