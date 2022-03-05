#include "Bull.h"
#include "Game.h"

Bull::Bull(Game* game, int Aleatorio, Point2D<int> centroRadio) : Enemy(game, Aleatorio, centroRadio)
{
	setTexture(bullTexture);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(100, 110);
	initialPos_ = getPosition();
	//createCheckPoints();
	stop = false;
	timer_ = SDL_GetTicks();
}

void Bull::update()
{
	move(1);
	checkDistance();
	//El toro si ha alcanzado al jugador se espera 1,5 segundos para volver a perseguirlo
	if (stop && SDL_GetTicks() > timer_ + 1500) {
		stop = false;
		timer_ = SDL_GetTicks();
	}
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
	int offset = 300;
	double dX = getPosition().getX() - game->getPosisitionPlayer().getX();
	double dY = getPosition().getY() - game->getPosisitionPlayer().getY();
	double distanceX = abs(dX);
	double distanceY = abs(dY);

	double newX = getPosition().getX(), newY = getPosition().getY();
	int speed = 5;
	//Si esta en el rango
	if (distanceX <= offset && distanceY <= offset && !stop) {
		cout << distanceX << " " << distanceY << endl;
		//Perseguir al jugador
		//Le persigue hasta estar a 5 de distacia
		if ((distanceX >= 3 || distanceY >= 3)) {
			if (distanceX >= 3 && distanceY < 3) {
				if (dX < 0) newX = getPosition().getX() + speed;
				else if (dX > 0) newX = getPosition().getX() - speed;
				setPosition(newX, getY());
			}
			else if (distanceY >= 3 && distanceX < 3) {
				if (dY < 0) newY = getPosition().getY() + speed;
				else if (dY > 0) newY = getPosition().getY() - speed;
				setPosition(getX(), newY);
			}
			else {
				if (dX < 0) newX = getPosition().getX() + speed/2.0;		//el mono esta a la derecha
				else if (dX > 0) newX = getPosition().getX() - speed / 2.0;	//el mono esta a la izquierda
				if (dY < 0) newY = getPosition().getY() + speed / 2.0;		//el mono esta por debajo
				else if (dY > 0) newY = getPosition().getY() - speed / 2.0;	//el mono esta por encima
				setPosition(newX, newY);
			}
		}
		 
		if (distanceX < 3 && distanceY < 3) stop = true;
		//si no es demasiado por eso se divide entre 8
		game->scare(distanceX * scariness_ / 10);
	}
}
