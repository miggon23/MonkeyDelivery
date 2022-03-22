#include "Scorpion.h"
#include "Game.h"

Scorpion::Scorpion(Game* game, int Aleatorio, Point2D<int> centroRadio, AnimationManager* animation) : Enemy(game, Aleatorio, centroRadio, animation)
{
	setTexture(scorpionSpritesheet);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(100, 110);
	initialPos_ = getPosition();
	createCheckPoints();
	lastUpdate_ = SDL_GetTicks();
	setScariness(0.1);
	iniPlayerVel = game->getPlayer()->getVel();
	inRange = false;
	setResistance(2500);
	textureRect = { 0, 0, animationManager->getWidthScorpion(),animationManager->getHeigthScorpion() };
}

void Scorpion::update()
{
	patrol(1);
	checkDistance();
	die();
}

void Scorpion::createCheckPoints()
{
	addCheckPoint(initialPos_);
	addCheckPoint(Point2D<double>(initialPos_.getX() + 70, initialPos_.getY() + 20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 120, initialPos_.getY() - 20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 190, initialPos_.getY()));
}

void Scorpion::checkDistance()
{
	if (lastUpdate_ + 1000 < SDL_GetTicks()) {
		int range = 50; //rango
		int distance = 300;
		double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX()); //distancia en valor absoluto en las x
		double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY()); //distacia en valor absoluto en las y

		double playerVel = game->getPlayer()->getVel();

		//Si esta en el rango
		if (distanceX <= range && distanceY <= range)
		{
			//Si la velocidad del jugador no ha sido reducida, es decir, no había entrado en el rango
			if (!inRange) { //playerVel > (iniPlayerVel / 2.0) + 0.05
				game->setVel(playerVel / 2.0);
				inRange = true;
			}
		}
		if (distanceX <= distance && distanceY <= distance) {
			double d = 1.8 * ((distanceY + distanceX) / 2);
			if (distanceX <= 20.0 && distanceY <= 20.0) {
				game->scare(2.0 * scariness_ / 10);
			}
			else game->scare(d * scariness_ / 10);

			lastUpdate_ = SDL_GetTicks();
		}
		//Si no esta en el rango la velocidad sera normal
		else if (inRange) //<-- En rango aún
		{
			game->getPlayer()->setVel(playerVel * 2.0);
			inRange = false;
		}
		lastUpdate_ = SDL_GetTicks();
	}
	//else { 
	//	
	//	//game->setVel(iniPlayerVel); // Esto hace que el jugador no pueda correr ni ir en bici ya que resetea la velocidad todo el rato <---
	//	//iniPlayerVel = game->getPlayer()->getVel();
	//} 
}

void Scorpion::draw()
{
	if (isAlive())
		animationManager->getFrameImageScorpion(getCollider(), textureRect, texture, timerAnimation);
}
