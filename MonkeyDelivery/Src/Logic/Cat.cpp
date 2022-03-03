#include "Cat.h"

Cat::Cat(Game* game,int Aleatorio, Point2D<int>centroRadio):Enemy(game, 50, centroRadio){
	zone = SpawnZone(Aleatorio, centroRadio);
	Vector2D<double> x = zone.genratePoint();
	std::cout << x.getX() << " " << x.getY();
	setPosition(x.getX(), x.getY());
	setTexture(catTexture);
	setDimension(90, 100);
	addCheckPoint(Point2D<double>(100, 100));
	setScariness(0.1);
}

void Cat::update()
{
	move(1);
	checkDistance();
}
