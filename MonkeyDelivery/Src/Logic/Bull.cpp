#include "Bull.h"
#include "Game.h"

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
	checkDistance();
}

void Bull::createCheckPoints()
{
	addCheckPoint(initialPos);
	addCheckPoint(Point2D<double>(initialPos.getX() + 70, initialPos.getY() + 20));
	addCheckPoint(Point2D<double>(initialPos.getX() + 120, initialPos.getY() -20));
	addCheckPoint(Point2D<double>(initialPos.getX() + 190, initialPos.getY()));
}

void Bull::checkDistance()
{
	int offset = 200;
	double dX = getPosition().getX() - game->getPosisitionPlayer().getX();
	double dY = getPosition().getY() - game->getPosisitionPlayer().getY();
	double distanceX = abs(dX);
	double distanceY = abs(dY);

	//Si esta en el rango
	if (distanceX <= offset && distanceY <= offset) {

		//Perseguir al jugador
		if (distanceX >= 5 && distanceY >= 5) {

			double newX=0, newY=0;
			int speed = 5;

			if (dX < 0) newX = getPosition().getX() + speed;
			else if (dX > 0) newX= getPosition().getX() - speed;
			if (dY < 0) newY = getPosition().getY() + speed;
			else if (dY > 0) newY = getPosition().getY() - speed;

			setPosition(newX, newY);

			//dY < 0 -> el mono esta por debajo
			//dY > 0 -> el mono esta por encima
			//dX < 0 ->el mono esta a la derecha
			//dX > 0 ->el mono esta a la izquierda
		}
		

		//si no es demasiado por eso se divide entre 8
		game->scare(distanceX * scariness_ / 10);
	}
}
