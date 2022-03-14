#include "Scorpion.h"
#include "Game.h"

Scorpion::Scorpion(Game* game, int Aleatorio, Point2D<int> centroRadio, AnimationManager* animation) : Enemy(game, Aleatorio, centroRadio, animation)
{
	setTexture(scorpionSpritesheet);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(100, 110);
	initialPos_ = getPosition();
	createCheckPoints();
	setScariness(0.1);

	timerAnimation = SDL_GetTicks();

	textureRect = { 0, 0, animationManager->getWidthScorpion(),animationManager->getHeigthScorpion()};
}

void Scorpion::update()
{
	patrol(1);
	checkDistance();
}

void Scorpion::createCheckPoints()
{
	addCheckPoint(initialPos_);
	addCheckPoint(Point2D<double>(initialPos_.getX() + 70, initialPos_.getY() + 20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 120, initialPos_.getY() - 20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 190, initialPos_.getY()));
}

//void Scorpion::checkDistance()
//{
//}

void Scorpion::draw()
{
	animationManager->getFrameImageScorpion(getCollider(), textureRect, texture, timerAnimation);
}
