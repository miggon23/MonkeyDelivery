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
	double energyDrinkSpeedBonus_ = 1.15;
	double energyDrinkEnergyBonus_ = 0.05;

	VirtualTimer* timerAntiBanana_;
	bool activatedAntiBanana;
	int antiBananaLimit_ = 60000;
	double antiBananaFearBuff_ = 1.3;


	double monkeycolaReduction_ = 0.2; //20%
	double monkeycolaReductionHigh_ = 0.3; //30%

	Texture* texFearBuff_;
	Texture* texEnergyBuff_;
	Texture* texSpeedBuff_;
	bool activateBoots_;
public:
	PowerUpsManager(Game* game,Player* player);
	~PowerUpsManager();
	void update();
	void draw();
	void InitTimer(PowerUps x);
	void desactivate(PowerUps x);
	void desactivateAllPowerUps();
	
};

