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
	float energyDrinkSpeedBonus_ = 1.15;
	float energyDrinkEnergyBonus_ = 0.05;

	VirtualTimer* timerAntiBanana_;
	bool activatedAntiBanana;
	int antiBananaLimit_ = 60000;
	float antiBananaFearBuff_ = 1.3;

	VirtualTimer* timerMonkeycola_;
	bool activatedMonkeycola;
	int monkeycolaLimit_ = 60000;
	float monkeycolaFearBuff_ = 1.3;

	Texture* texFearBuff_;
	Texture* texEnergyBuff_;
	Texture* texSpeedBuff_;
	bool activateBoots_;
	const int NUMER_ITEMS = 2;
public:
	PowerUpsManager(Game* game,Player* player);
	~PowerUpsManager();
	void update();
	void draw();
	void InitTimer(PowerUps x);
	void desactivate(PowerUps x);
};

