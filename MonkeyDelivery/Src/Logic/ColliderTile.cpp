#include "ColliderTile.h"
#include "Game.h"

void ColliderTile::update()
{
	if (collide(game->getPlayer()->getCollider())) {
		isColliding_ = true;
		onPlayerCollision();
	}
	else if (isColliding_) { // La colisión estaba activa pero ha parado
		 
		isColliding_ = false;
		onPlayerCollisionExit();
	}
}

void ColliderTile::onPlayerCollision()
{
	auto player = game->getPlayer();
	Vector2D<double> pTopLeft = player->getPosition();
	Vector2D<double> pBottomLeft = {pTopLeft.getX(), pTopLeft.getY() + player->getHeight()};
	Vector2D<double> pTopRight = { pTopLeft.getX() + player->getWidth(), pTopLeft.getY() };
	Vector2D<double> pBottomRight = { pTopLeft.getX() + player->getWidth(), pTopLeft.getY() + player->getHeight() };
	int dir = -1;

	// && bottomLeft.getX() <= pTopRight.getX() && bottomRight.getX() >= pTopLeft.getX()
	//if (bottomLeft.getY() <= pTopLeft.getY()) {
	//	dir = Directions::UP;
	//}
	//else if (topLeft.getY()  >= pBottomLeft.getY()) {
	//	dir = Directions::DOWN;
	//}
	//else if (topLeft.getY()  >= pBottomLeft.getY()) {
	//	dir = Directions::DOWN;
	//}
	//else if (topLeft.getY()  >= pBottomLeft.getY()) {
	//	dir = Directions::DOWN;
	//}

	//if (getPosition().getX() > player->getPosition().getX()) {
	//	// Obstáculo a la derecha
	//	dir = Directions::RIGHT;
	//}
	//else if (getPosition().getX() < player->getPosition().getX()) {
	//	// Obstáculo a la izquierda
	//	dir = Directions::LEFT;
	//}
	//else if (getPosition().getY() > player->getPosition().getY()) {
	//	// Obstáculo abajo
	//	dir = Directions::DOWN;
	//}
	//else if (getPosition().getY() < player->getPosition().getY()) {
	//	// Obstáculo arriba
	//	dir = Directions::UP;
	//}

	//player->onCollision(dir);
}

void ColliderTile::onPlayerCollisionExit()
{
	auto player = game->getPlayer();
	int dir = -1;
	if (getPosition().getX() > player->getPosition().getX()) {
		// Obstáculo a la derecha
		dir = Directions::RIGHT;
	}
	else if (getPosition().getX() < player->getPosition().getX()) {
		// Obstáculo a la izquierda
		dir = Directions::LEFT;
	}
	else if (getPosition().getY() > player->getPosition().getY()) {
		// Obstáculo abajo
		dir = Directions::DOWN;
	}
	else if (getPosition().getY() < player->getPosition().getY()) {
		// Obstáculo arriba
		dir = Directions::UP;
	}
	player->onCollisionExit(dir);
}
