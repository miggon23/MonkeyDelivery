#pragma once
#include "Enemy.h"
class Bull : public Enemy
{
private:

	Point2D<double> initialPos_;
	bool stop; //Evita que el toro persiga al jugador cuando ya lo ha alcanzado
	int timer_; //Temporizador para el tiempo que el toro tiene stop activo

public:
	Bull(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Bull() {};

	void update() override;
	void createCheckPoints() override;
	void checkDistance() override;
};

