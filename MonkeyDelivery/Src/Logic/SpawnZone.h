#pragma once
#include "../utils/Vector2D.h"
class SpawnZone
{
	int RadioSpawn;
	Point2D<int> centro;
public:
	SpawnZone();
	SpawnZone(int radio, Point2D<int> centro);
	~SpawnZone();
	Vector2D<double>generatePoint();
};

