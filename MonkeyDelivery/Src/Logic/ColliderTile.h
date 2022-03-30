#pragma once
#include "../utils/Vector2D.h"

#include "GameObject.h"
class Game;

class ColliderTile : public GameObject
{
public:
	ColliderTile(Game* g, Vector2D<double> p, int w, int h) : GameObject(g){
		setPosition(p.getX(), p.getY());
		setDimension(w, h);
	};

	void update() override {};
};

