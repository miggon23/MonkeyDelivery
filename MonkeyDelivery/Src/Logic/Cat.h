#pragma once

#include "Enemy.h"

class Cat : public Enemy
{
protected:

	double speed;
	Point2D<double> initialPos;

public:

	Cat(Game* game, int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation);
	~Cat() {};

	void update() override;
	void createCheckPoints() override;
	void draw() override;
	void checkDistance() override;
};

