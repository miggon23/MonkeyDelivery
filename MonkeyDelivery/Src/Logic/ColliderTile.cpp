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
		onPlayerExitCollision();
	}
}

void ColliderTile::onPlayerCollision()
{
}

void ColliderTile::onPlayerExitCollision()
{
}
