#include "PowerUpsManager.h"
#include "Game.h"
#include "../Player/Player.h"
#include "../sdlutils/VirtualTimer.h"
PowerUpsManager::PowerUpsManager(Game* game, Player* player):game_(game),player_(player),
activatedEnergyDrink_(false),activateBoots_(false),timerEnergyDrink_(new VirtualTimer()),
activatedFearBuff(false),timerFearBuff_(new VirtualTimer()){
	texEnergyBuff_ = game->getTexture(UI_energyBuff);
	texFearBuff_ = game->getTexture(UI_fearBuff);
	texSpeedBuff_ = game->getTexture(UI_speedBuff);
}

PowerUpsManager::~PowerUpsManager(){
	player_ = nullptr;
	game_ = nullptr;
	delete timerEnergyDrink_;
	delete timerFearBuff_;
	timerEnergyDrink_ = nullptr;
	timerFearBuff_ = nullptr;
	texEnergyBuff_ = nullptr;
	texFearBuff_ = nullptr;
	texSpeedBuff_ = nullptr;
}

void PowerUpsManager::update(){
	if (activatedEnergyDrink_) {
		if (timerEnergyDrink_->currTime() >= timeEnergyDrinkLimit_) {
			player_->resetVelocity();
			player_->setBonusSpending(0.0);
			activatedEnergyDrink_ = false;
			timerEnergyDrink_->pause();
			std::cout << "energydrink desactivado" << std::endl;
		}
	}
	if (activatedFearBuff) {

	}
}
void PowerUpsManager::draw(){
	double aux=1.2;
	if (activatedEnergyDrink_) {

		//Mostrar el ICONO SPEED
		SDL_Rect rect = { (int)game_->getWindowWidth()*aux/ 3,(int)game_->getWindowHeight() * 3.5 / 4 -20 ,texSpeedBuff_->getW()*5,texSpeedBuff_->getH()*5 };		
		texEnergyBuff_->render(rect);
		
	}
	aux += 0.2;
	if (activateBoots_||activatedEnergyDrink_) {
		//MOSTAR EL ICONO ENERGY
		SDL_Rect rect = { (int)game_->getWindowWidth() * aux / 3,(int)game_->getWindowHeight() * 3.5 / 4 - 20 ,texSpeedBuff_->getW() * 5,texSpeedBuff_->getH() * 5 };
		texSpeedBuff_->render(rect);
	}
	aux += 0.2;
	if (activatedFearBuff) {
		//MOSTAR EL ICONO FEAR
		SDL_Rect rect = { (int)game_->getWindowWidth() * aux / 3,(int)game_->getWindowHeight() * 3.5 / 4 - 20 ,texSpeedBuff_->getW() * 5,texSpeedBuff_->getH() * 5 };
		texFearBuff_->render(rect);
	}
}
void PowerUpsManager::InitTimer(PowerUps x){
	switch (x){
	case energyDrink:
		activatedEnergyDrink_ = true;
		timerEnergyDrink_->reset();
		break;
	case boots:
		activateBoots_ = !activateBoots_;
	default:
		break;
	}
}
