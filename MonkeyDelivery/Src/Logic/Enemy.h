#pragma once
#include "GameObject.h"
#include "SpawnZone.h"
class Enemy : public GameObject
{
private:

	double speed;
	bool alive;
	int scariness;
	float dieTime;
	SpawnZone zone;
public:

	Enemy(Game* game, int Aleatorio,Point2D<int>centroRadio);
	~Enemy() {};

	void move(double speed);

	void die();

	inline bool isAlive() { return alive; };
	inline void setAlive(bool l) { alive = l; };

	void spawn();
	void onCollision();
	void  update() override;
	void draw() override;
};

