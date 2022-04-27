#pragma once
#include "../utils/Vector2D.h"

#include "GameObject.h"
#include "../Player/Player.h"
class Game;

class ColliderTile : public GameObject
{
protected:
	bool isActive_ = true; // para el libro tutorial, colliders que en algun momento se desactivan
	bool isColliding_ = false;

private:

	Vector2D<double> topLeft_, topRight_, bottomLeft_, bottomRight_;
	double margin_ = 5.0; // Margen para comprobar por qué lado se está haciendo la colisión

	Directions chooseDirection(Player* player);
public:
	ColliderTile(Game* g, Vector2D<double> p, double w, double h) : GameObject(g, true){
		setPosition(p.getX(), p.getY());
		setDimension(w, h);
		topLeft_ = p;
		topRight_ = { p.getX() + w, p.getY() };
		bottomLeft_ = { p.getX(), p.getY() + h };
		bottomRight_ = { p.getX() + w, p.getY() + h };
	};

	void update() override;

	void onPlayerCollision();
	void onPlayerCollisionExit();
};

