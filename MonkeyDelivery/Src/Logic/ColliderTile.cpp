#include "ColliderTile.h"
#include "Game.h"

Directions ColliderTile::chooseDirection(Player* player)
{
	margin_ = 20.0;

	Vector2D<double> pTopLeft = player->getPosition();
	Vector2D<double> pBottomLeft = { pTopLeft.getX(), pTopLeft.getY() + player->getHeight() };
	Vector2D<double> pTopRight = { pTopLeft.getX() + player->getWidth(), pTopLeft.getY() };

	if (bottomLeft_.getY() <= pTopLeft.getY() + margin_) {
		return Directions::UP;
	}
	else if (topLeft_.getY() >= pBottomLeft.getY() - margin_) {
		return Directions::DOWN;
	}
	else if (topLeft_.getX() >= pTopRight.getX() - margin_) {
		return Directions::RIGHT;
	}
	else { // if (topRight_.getX() <= pTopLeft().getX() + margin_)
		return Directions::LEFT;
	}
}

void ColliderTile::update()
{
	if (isActive_) {
		if (collide(game->getPlayer()->getCollider())) {
			isColliding_ = true;
			onPlayerCollision();
		}
		else if (isColliding_) { // La colisión estaba activa pero ha parado
		 
			isColliding_ = false;
			onPlayerCollisionExit();
		}
	}
}

void ColliderTile::onPlayerCollision()
{
	auto player = game->getPlayer();
	int dir = chooseDirection(player);
	player->onCollision(dir);
}

void ColliderTile::onPlayerCollisionExit()
{
	game->getPlayer()->onCollisionExit();
}
