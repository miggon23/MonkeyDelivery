#include "Bull.h"
#include "Game.h"

Bull::Bull(Game* game, int Aleatorio, Point2D<int> centroRadio) : Enemy(game, Aleatorio, centroRadio)
{
	setTexture(bullTexture);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(100, 110);
	initialPos_ = getPosition();
	createCheckPoints();
	stop = true; //Patrulla y no persigue
}

void Bull::update()
{
	if(stop) move(1); //El toro solo patrulla si no persigue 
	checkDistance();
	//Si han pasado 3 segundos y el toro esta persiguiendo
	if (!stop && SDL_GetTicks() > timer_ + 3000) {
		stop = true;
	}
	cout << stop << endl;
}

void Bull::createCheckPoints()
{
	addCheckPoint(initialPos_);
	addCheckPoint(Point2D<double>(initialPos_.getX() + 70, initialPos_.getY() + 20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 120, initialPos_.getY() -20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 190, initialPos_.getY()));
}

void Bull::checkDistance()
{
	int offset = 300; //rango
	double dX = getPosition().getX() - game->getPosisitionPlayer().getX();
	double dY = getPosition().getY() - game->getPosisitionPlayer().getY();
	double distanceX = abs(dX);
	double distanceY = abs(dY);

	double newX = getPosition().getX(), newY = getPosition().getY();
	int speed = 2;
	//Si esta en el rango
	if (distanceX <= offset && distanceY <= offset) {
		stop = false; //Persigo
		timer_ = SDL_GetTicks();
		//Perseguir al jugador
		if (dX < 0) newX = getPosition().getX() + speed / 2.0;		//el mono esta a la derecha
		else if (dX > 0) newX = getPosition().getX() - speed / 2.0;	//el mono esta a la izquierda
		if (dY < 0) newY = getPosition().getY() + speed / 2.0;		//el mono esta por debajo
		else if (dY > 0) newY = getPosition().getY() - speed / 2.0;	//el mono esta por encima
		setPosition(newX, newY);
		
		//si no es demasiado por eso se divide entre 8
		game->scare(distanceX * scariness_ / 10);
	}
	else if(SDL_GetTicks() > timer_ + 3000) 
	{ 
		stop = true; 
	}
	else {
		if (dX < 0) newX = getPosition().getX() + speed / 2.0;		//el mono esta a la derecha
		else if (dX > 0) newX = getPosition().getX() - speed / 2.0;	//el mono esta a la izquierda
		if (dY < 0) newY = getPosition().getY() + speed / 2.0;		//el mono esta por debajo
		else if (dY > 0) newY = getPosition().getY() - speed / 2.0;	//el mono esta por encima
		setPosition(newX, newY);
	}
}
//stop=true --> Patrulla y no persigue
//stop=false -->Persigue y no patrulla