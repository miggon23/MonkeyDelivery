#include "SpawnZone.h"
#include <ctime>

SpawnZone::SpawnZone()
{
	
}

SpawnZone::SpawnZone(int radio, Point2D<int> centro) :RadioSpawn(radio), centro(centro)
{
	
}

SpawnZone::~SpawnZone()
{
}

Vector2D<double> SpawnZone::generatePoint()
{
	srand(time(NULL));
	Point2D<double> pos;
	pos.setX(rand() % -RadioSpawn + RadioSpawn);
	pos.setY(rand() % -RadioSpawn + RadioSpawn);
	pos.set(pos.getX()+centro.getX(),pos.getY()+centro.getY());
	return pos;
}
