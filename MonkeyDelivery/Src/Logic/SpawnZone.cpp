#include "SpawnZone.h"
#include <ctime>
#include "../sdlutils/SDLUtils.h"

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
	pos.setX(sdlutils().rand().nextInt(-RadioSpawn, RadioSpawn));
	pos.setY(sdlutils().rand().nextInt(-RadioSpawn, RadioSpawn));
	pos.set(pos.getX()+centro.getX(),pos.getY()+centro.getY());
	return pos;
}
