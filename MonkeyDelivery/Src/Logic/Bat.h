#pragma once
#include "Enemy.h"

class Bat : public Enemy
{

	int coinLost_;
	Player* player_;

public:

	Bat(Game* game, int Aleatorio, Point2D<int>centroRadio, int nLoop);
	~Bat() {};

	void update() override;

	void onPlayerInteraction(Player* player) override;
};
