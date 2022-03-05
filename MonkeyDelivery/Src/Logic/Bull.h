#pragma once
#include "Enemy.h"
class Bull : public Enemy
{
private:

	Point2D<double> initialPos;

public:
	Bull(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Bull() {};

	void update() override;
	void createCheckPoints() override;
	void checkDistance() override;
};

