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
	
	int indexCheckPoint;
	bool back;

public:

	Cat(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Cat() {};

	virtual void move(double speed);

	void die();

	inline bool isAlive() { return alive; };
	inline void setAlive(bool l) { alive = l; };
	inline void addCheckPoint(Point2D<double> punto) { checkpoints.push_back(punto); };

	void spawn();
	void onCollision();
	void update() {};
	void draw() override {drawTexture(texture);}
};

