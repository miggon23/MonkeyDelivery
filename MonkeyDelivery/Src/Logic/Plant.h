#pragma once
#include "Enemy.h"

class Plant : public Enemy
{
public:
	Plant(Game* game, int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation);
	~Plant() {};

	void update() override;
	void createCheckPoints() override {};
	void checkDistance() override;
	void draw() override;
};

