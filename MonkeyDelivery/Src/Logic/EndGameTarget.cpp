#include "EndGameTarget.h"
#include "Game.h"
EndGameTarget::EndGameTarget(Game* g, AnimationManager* animation) : GameObject(g, true)
{
	texture = game->getTexture(npc_Coco);
	Point2D<double> relative = { (double)(game->getWindowWidth() / 1800), (double)(game->getWindowHeight() / 1000) };
	setPosition(1800*relative.getX(), 6500*relative.getY()); // en la playa
	setDimension(60, 60);

	textureRect = { 0, 0, 60, 60 };
}

EndGameTarget::~EndGameTarget()
{
}

void EndGameTarget::onPlayerInteraction(Player* player)
{
	//cinematica
}

void EndGameTarget::draw()
{
	SDL_Rect pos = getCollider();

	//Dibujamos respecto a la camara
	pos.x -= (int)game->getCamera()->getCameraPosition().getX();
	pos.y -= (int)game->getCamera()->getCameraPosition().getY();

	animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
}
