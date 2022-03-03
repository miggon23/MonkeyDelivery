#pragma once

#include "Enemy.h"

class Cat : public Enemy
{
protected:

	double speed;
	bool alive;
	int scariness;
	float dieTime;
	SpawnZone zone;
	vector<Point2D<double>> checkpoints;
	double fear_;
	
	int indexCheckPoint;
	bool back;

public:

	Cat(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Cat() {};

	inline void update() override { move(1); checkDistance(); }
	void draw() override {drawTexture(texture);}
	/*a continuacion, metodos EN PRUEBAS para el miedo
	 posteriormente se integraran en enemy
	*/
	inline void setFear(double fear) { fear_ = fear; }
};

