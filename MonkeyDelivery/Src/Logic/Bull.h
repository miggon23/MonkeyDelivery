#pragma once
#include "Enemy.h"
class Bull : public Enemy
{
private:

public:
	Bull(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Bull() {};

	void update() override;
};

