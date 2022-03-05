#include "Bull.h"

Bull::Bull(Game* game, int Aleatorio, Point2D<int> centroRadio) : Enemy(game, Aleatorio, centroRadio)
{
	setTexture(bullTexture);
	Vector2D<double> x = zone.genratePoint();
	setPosition(x.getX(), x.getY());
	setDimension(90, 100);
	addCheckPoint(getPosition());
}

void Bull::update()
{
	move(1);
}
