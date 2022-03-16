#include "Plant.h"
#include "Game.h"

Plant::Plant(Game* game, int Aleatorio, Point2D<int> centroRadio, AnimationManager* animation):Enemy(game, Aleatorio, centroRadio, animation)
{
	Vector2D<double> zonePoint = zone.generatePoint(); //genera un punto en la zona de spawn
	setPosition(zonePoint.getX(), zonePoint.getY()); //Coloca al enemigo en ese punto
	setTexture(plantSpritesheet);
	setDimension(80, 90);
	timerAnimation = SDL_GetTicks();

	textureRect = { 0, 0, animationManager->getWidthPlant(),animationManager->getHeigthPlant() };
}

void Plant::update()
{
	checkDistance();
}

void Plant::checkDistance()
{

}

void Plant::draw()
{
	animationManager->getFrameImagePlant(getCollider(), textureRect, texture, timerAnimation);
}
