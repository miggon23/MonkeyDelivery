#pragma once
#include "../utils/Vector2D.h"

#include "GameObject.h"
class Game;

class ColliderTile : public GameObject
{
private:
	bool isColliding_ = false;
public:
	ColliderTile(Game* g, Vector2D<double> p, int w, int h) : GameObject(g, true){
		setPosition(p.getX(), p.getY());
		setDimension(w, h);
	};

	void update() override;

	void onPlayerCollision();
	void onPlayerExitCollision();
};

