#pragma once
#include "Enemy.h"

class Bat : public Enemy
{
	Point2D<double> initialPos;
	int coinLost_;
	Player* player_;
	int loops;
	Uint32 stealTimer_;

public:

	Bat(Game* game, int Aleatorio, Point2D<int>centroRadio, int nLoop);
	~Bat() {};

	void update() override;
	void createCheckPoints() override;
	void onPlayerInteraction(Player* player) override;
	void draw() override;
};
