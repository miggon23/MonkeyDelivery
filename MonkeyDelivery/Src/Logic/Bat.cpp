#include "Bat.h"
#include "..\..\Bat.h"


Bat::Bat(Game* game, int Aleatorio, Point2D<int> centroRadio): Enemy(game, Aleatorio, centroRadio)
{
	speed = 5;

	addCheckPoint(getPosition());
	
	for (int i = 0; i < 100; i++)
	{
		addCheckPoint(getPosition());
	}


}

