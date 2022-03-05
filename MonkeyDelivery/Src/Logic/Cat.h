#pragma once

#include "Enemy.h"

class Cat : public Enemy
{
protected:

	double speed;
	float dieTime;
	Point2D<double> initialPos;

public:

	Cat(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Cat() {};

	void update() override;
	void createCheckPoints() override;
};

