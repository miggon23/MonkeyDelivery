#pragma once
#include "Enemy.h"

class Scorpion : public Enemy
{
private:

	Point2D<double> initialPos_;
	int timer_; //Temporizador para el tiempo que el toro tiene stop activo
	double speed = 2;
	double iniPlayerVel;
	//Usamos un booleano de inRange para saber cuando el jugador entra y sale del rango,
	//estio onCollisionEnter y onCollisionExit de Unity
	bool inRange; 
	bool attacked = false;

public:
	Scorpion(Game* game, int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation);
	~Scorpion() {};

	void update() override;
	void createCheckPoints() override;
	void checkDistance() override;

	void draw() override;
};

