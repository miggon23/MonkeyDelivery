#pragma once
#include "Enemy.h"

class Bat : public Enemy
{

	int coinLost;

public:

	Bat(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Bat() {};
	
	void update() override;
	void draw() override;
};



