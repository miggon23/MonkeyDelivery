#pragma once
#include "../Player/Player.h"
//class Player;
class VirtualTimer;
class Game;

class PowerUpsManager{
	Player* player_;
	Game* game_;
	//necesitaremos un timer por powerUp y un booleano, además del efecto que produzca
	VirtualTimer* timerEnergyDrink_;
	bool activatedEnergyDrink_;
	int timeEnergyDrinkLimit_ = 30000;
	double energyDrinkSpeedBonus_ = 1.05;
	double energyDrinkEnergyBonus_ = 0.05;

	VirtualTimer* timerAntiBanana_;
	bool activatedAntiBanana;
	int antiBananaLimit_ = 60000;
	int antiBananaLimitFecoverFear_ = 2000;
	double antiBananaFearBuff_ = 1.3;
	double  antiBananaFearRecoverBuff_ = 0.15;

	double monkeycolaReduction_ = 0.2; //20%
	double monkeycolaReductionHigh_ = 0.3; //30%

	double bananaBuff_ = 0.1; //10%
	double bananaBuffHigh_ = 0.25;//25%

	Texture* texFearBuff_;
	Texture* texEnergyBuff_;
	Texture* texSpeedBuff_;
	Texture* texSpeedDebuff_;
	bool activateBoots_;

	double speedNormalBootsMult_ = 1.2;
public:
	PowerUpsManager(Game* game,Player* player);
	~PowerUpsManager();
	void update();
	void draw();
	void ActivatePowerUp(PowerUps x);
	void desactivate(PowerUps x);
	void desactivateAllPowerUps();
	
	void onPauseEnter();
	void onPauseExit();
	inline bool playerHasBoots() { return activateBoots_; };
};

