#pragma once
#include "GameObject.h"
#include "SpawnZone.h"

class Enemy : public GameObject
{
protected:

	double speed;
	bool alive;
	double scariness_;
	float dieTime;
	SpawnZone zone;
	vector<Point2D<double>> checkpoints;
	int indexCheckPoint;
	bool back;

public:

	Enemy(Game* game, int Aleatorio, Point2D<int>centroRadio);
	~Enemy() {};

	 void move(double speed);

	void die();

	inline bool isAlive() { return alive; };
	inline void setAlive(bool l) { alive = l; };
	inline void addCheckPoint(Point2D<double> punto) { checkpoints.push_back(punto); };

	void spawn();
	void onCollision();
	virtual void checkDistance();
	virtual void setScariness(double fear) { scariness_ = fear; }
};

