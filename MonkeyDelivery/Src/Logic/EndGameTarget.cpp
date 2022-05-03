#include "EndGameTarget.h"
#include "Game.h"
EndGameTarget::EndGameTarget(Game* g, AnimationManager* animation) : GameObject(g, true)
{
	setTexture(npc_Coco);
	// setPosition(); // en la playa
	setDimension(60, 60);
}

EndGameTarget::~EndGameTarget()
{
}

void EndGameTarget::onPlayerInteraction(Player* player)
{
	// game->endGameCinematic();
}

void EndGameTarget::draw()
{
	SDL_Rect pos = getCollider();

	//Dibujamos respecto a la camara
	pos.x -= (int)game->getCamera()->getCameraPosition().getX();
	pos.y -= (int)game->getCamera()->getCameraPosition().getY();

	animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
}
