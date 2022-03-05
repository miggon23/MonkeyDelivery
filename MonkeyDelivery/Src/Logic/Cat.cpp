#include "Cat.h"

Cat::Cat(Game* game,int Aleatorio, Point2D<int>centroRadio):Enemy(game, Aleatorio, centroRadio){
	zone = SpawnZone(Aleatorio, centroRadio);
	Vector2D<double> x = zone.generatePoint();
	setPosition(x.getX(), x.getY());
	initialPos = getPosition();
	setTexture(catTexture);
	setDimension(70, 80);
	createCheckPoints();
	setScariness(0.1);
}

void Cat::update()
{
	move(1);
	checkDistance();
}

void Cat::createCheckPoints()
{
	int offset = 30;

	addCheckPoint(initialPos);
	addCheckPoint(Point2D<double>(initialPos.getX() + offset, initialPos.getY() - offset));
	addCheckPoint(Point2D<double>(initialPos.getX(), initialPos.getY() - offset*2));
	addCheckPoint(Point2D<double>(initialPos.getX() - offset, initialPos.getY() - offset));
	addCheckPoint(initialPos);
}
