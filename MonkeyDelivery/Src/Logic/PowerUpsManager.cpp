#include "PowerUpsManager.h"
#include "Game.h"
#include "../Player/Player.h"
#include "../sdlutils/VirtualTimer.h"
PowerUpsManager::PowerUpsManager(Game* game, Player* player):game_(game),player_(player),
activatedEnergyDrink_(false),activateBoots_(false),timerEnergyDrink_(new VirtualTimer()),
activatedAntiBanana(false), timerAntiBanana_(new VirtualTimer()){

	texEnergyBuff_ = game->getTexture(UI_energyBuff);
	texFearBuff_ = game->getTexture(UI_fearBuff);
	texSpeedBuff_ = game->getTexture(UI_speedBuff);
}

PowerUpsManager::~PowerUpsManager(){
	player_ = nullptr;
	game_ = nullptr;
	delete timerEnergyDrink_;
	delete timerAntiBanana_;
	timerEnergyDrink_ = nullptr;
	timerAntiBanana_ = nullptr;
	texEnergyBuff_ = nullptr;
	texFearBuff_ = nullptr;
	texSpeedBuff_ = nullptr;
}

void PowerUpsManager::update(){
	if (activatedEnergyDrink_) {
		if (timerEnergyDrink_->currTime() >= timeEnergyDrinkLimit_) {
			desactivate(energyDrink);
		}
	}
	if (activatedAntiBanana) {
		if (timerAntiBanana_->currTime() >= timeEnergyDrinkLimit_) {
			desactivate(repelente);
		}
	}
}
void PowerUpsManager::draw(){
	double aux=1.2;
	if (activatedEnergyDrink_) {

		//Mostrar el ICONO SPEED
		SDL_Rect rect = { (int)(game_->getWindowWidth()*aux/ 3),(int)(game_->getWindowHeight() * 3.5 / 4 -20) ,texSpeedBuff_->getW()*5,texSpeedBuff_->getH()*5 };		
		texEnergyBuff_->render(rect);
		
	}
	aux += 0.2;
	if (activateBoots_||activatedEnergyDrink_) {
		//MOSTAR EL ICONO ENERGY
		SDL_Rect rect = { (int)(game_->getWindowWidth() * aux / 3),(int)(game_->getWindowHeight() * 3.5 / 4 - 20 ),texSpeedBuff_->getW() * 5,texSpeedBuff_->getH() * 5 };
		texSpeedBuff_->render(rect);
	}
	aux += 0.2;
	if (activatedAntiBanana) {
		//MOSTAR EL ICONO FEAR
		SDL_Rect rect = { (int)(game_->getWindowWidth() * aux / 3),(int)(game_->getWindowHeight() * 3.5 / 4 - 20) ,texSpeedBuff_->getW() * 5,texSpeedBuff_->getH() * 5 };
		texFearBuff_->render(rect);
	}
}
void PowerUpsManager::ActivatePowerUp(PowerUps x){
	switch (x){
	case energyDrink:
		//Si no estaba activado el energy drink
		if (!activatedEnergyDrink_) {
			//Aplicamos el PU al player
			player_->setVel(player_->getVel() * energyDrinkSpeedBonus_); 
			player_->drainEnergy(-(player_->getMaxEnergy() * energyDrinkEnergyBonus_));
			player_->setBonusSpending(energyDrinkEnergyBonus_);
			activatedEnergyDrink_ = true; //Activamos el PU
			timerEnergyDrink_->reset(); //Inicializamos el timer
		}else
			timerEnergyDrink_->reset();
		break;
	case boots:
		activateBoots_ = !activateBoots_;
		break;
	case banana:
		//Si es menor que el 10%
		if(player_->getEnergy() / player_->getMaxEnergy() < 0.1)
			player_->drainEnergy(-(player_->getMaxEnergy() * bananaBuffHigh_)); //sobre el total de enería
		else
			player_->drainEnergy(-(player_->getEnergy() * bananaBuff_)); //sobre la energía actual
		break;
	case monkeycola:
		//Menor que 80%, recupera el 20% del miedo
		if (player_->getFearPercent() < 80.0)
			player_->recoverFear(player_->getFear() * monkeycolaReduction_);
		else
			player_->recoverFear(player_->getFear() * monkeycolaReductionHigh_);
		
		break;
	case repelente:
		if (!activatedAntiBanana){
			player_->setFearBonusFactor(antiBananaFearBuff_);
			activatedAntiBanana = true;
			timerAntiBanana_->reset();
		}else
			timerAntiBanana_->reset();
		break;
	default:
		break;
	}
}

void PowerUpsManager::desactivate(PowerUps x)
{
	switch (x){
	case energyDrink:
		player_->setVel(player_->getVel() / energyDrinkSpeedBonus_);
		player_->setBonusSpending(0.0);
		activatedEnergyDrink_ = false;
		timerEnergyDrink_->pause();
		std::cout << "energydrink desactivado" << std::endl;
		break;
	case repelente:
		player_->setFearBonusFactor(1);
		activatedAntiBanana = false;
		timerAntiBanana_->pause();
		std::cout << "antibanana desactivado" << std::endl;
		break;
	default:
		break;
	}
}

void PowerUpsManager::desactivateAllPowerUps(){
	desactivate(energyDrink);
	desactivate(repelente);
}
