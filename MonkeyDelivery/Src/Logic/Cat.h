#pragma once

#include "Enemy.h"

class Cat : public Enemy
{
protected:

	double speed;
	bool alive;
	int scariness_;
	float dieTime;
	SpawnZone zone;
	vector<Point2D<double>> checkpoints;
	
	
	int indexCheckPoint;
	bool back;

public:

	Cat(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Cat() {};

	void update() override;
	void draw() override {drawTexture(texture);}
	/*a continuacion, metodos EN PRUEBAS para el miedo
	 posteriormente se integraran en enemy
	*/
	
};

