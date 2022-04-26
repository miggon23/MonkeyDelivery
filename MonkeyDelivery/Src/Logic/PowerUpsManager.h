#pragma once
#include "../Player/Player.h"
//class Player;
class VirtualTimer;
class Game;

class PowerUpsManager{
	Player* player_;
	Game* game_;
	//necesitaremos un timer por powerUp y un booleano
	VirtualTimer* timerEnergyDrink_;
	bool activatedEnergyDrink_;
	int timeEnergyDrinkLimit_ = 30000;

	VirtualTimer* timerFearBuff_;
	bool activatedFearBuff;
	int timeFearLimit_ = 30000;

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

