#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
private:

	double speed;
	bool alive;
	int scariness;
	float dieTime;

public:

	Enemy(Game* game);
	~Enemy() {};

	void move(double speed);

	void die();

	inline bool isAlive() { return alive; };
	inline void setAlive(bool l) { alive = l; };

	virtual void onCollision();
};

