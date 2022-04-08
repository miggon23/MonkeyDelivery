#pragma once
#include "../utils/Vector2D.h"

#include "GameObject.h"
class Game;

class ColliderTile : public GameObject
{
private:
	bool isColliding_ = false;

	Vector2D<double> topLeft, topRight, bottomLeft, bottomRight;

public:
	ColliderTile(Game* g, Vector2D<double> p, int w, int h) : GameObject(g, true){
		setPosition(p.getX(), p.getY());
		setDimension(w, h);
		topLeft = p;
		topRight = { p.getX() + w, p.getY() };
		bottomLeft = { p.getX(), p.getY() + h };
		bottomRight = { p.getX() + w, p.getY() + h };
	};

	void update() override;

	void onPlayerCollision();
	void onPlayerCollisionExit();
};

