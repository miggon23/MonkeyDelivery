#include "Bull.h"

Bull::Bull(Game* game, int Aleatorio, Point2D<int> centroRadio) : Enemy(game, Aleatorio, centroRadio)
{
	setTexture(bullTexture);
	Vector2D<double> x = zone.generatePoint();
	setPosition(x.getX(), x.getY());
	setDimension(90, 100);
	initialPos = getPosition();
	createCheckPoints();
}

void Bull::update()
{
	move(1);
}

void Bull::createCheckPoints()
{
	addCheckPoint(initialPos);
	addCheckPoint(Point2D<double>(initialPos.getX() + 70, initialPos.getY() + 20));
	addCheckPoint(Point2D<double>(initialPos.getX() + 120, initialPos.getY() -20));
	addCheckPoint(Point2D<double>(initialPos.getX() + 190, initialPos.getY()));
}
