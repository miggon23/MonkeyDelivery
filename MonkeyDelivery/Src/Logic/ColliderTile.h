#pragma once
#include "../utils/Vector2D.h"

#include "GameObject.h"
class Game;

class ColliderTile : public GameObject
{
public:
	ColliderTile(Game* g, Vector2D<double> p, int s) : GameObject(g){
		setPosition(p.getX(), p.getY());
		setDimension(s, s);
	};
	~ColliderTile();

	void update() override {};
};

