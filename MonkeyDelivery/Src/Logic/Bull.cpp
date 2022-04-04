#include "Bull.h"
#include "Game.h"

Bull::Bull(Game* game, int Aleatorio, Point2D<int> centroRadio, AnimationManager* animation) : Enemy(game, Aleatorio, centroRadio, animation)
{
	setTexture(bullspritesheet);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(120, 120);
	initialPos_ = getPosition();
	createCheckPoints();
	lastUpdate_ = SDL_GetTicks();
	stop = true; //Patrulla y no persigue
	setScariness(0.15);
	setResistance(1500);


	textureRect = { 0, 0, animationManager->getWidthBull(),animationManager->getHeigthBull() };
}

void Bull::update()
{
	if (stop) patrol(1); //El toro solo patrulla si no persigue 
	checkDistance();
	bullScares();
	die();
	respawn();
	//Si han pasado 3 segundos y el toro esta persiguiendo
	if (!stop && SDL_GetTicks() > timer_ + 3000) {
		stop = true;
	}
}

void Bull::createCheckPoints()
{
	addCheckPoint(initialPos_);
	addCheckPoint(Point2D<double>(initialPos_.getX() + 70, initialPos_.getY() + 20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 120, initialPos_.getY() - 20));
	addCheckPoint(Point2D<double>(initialPos_.getX() + 190, initialPos_.getY()));
}

void Bull::chase(double x, double y)
{
	double newX = getPosition().getX(), newY = getPosition().getY();
	if (x < -1) newX = getPosition().getX() + speed / 2.0;		//el mono esta a la derecha
	else if (x > 1) newX = getPosition().getX() - speed / 2.0;	//el mono esta a la izquierda
	if (y < -1) newY = getPosition().getY() + speed / 2.0;		//el mono esta por debajo
	else if (y > 1) newY = getPosition().getY() - speed / 2.0;	//el mono esta por encima
	setPosition(newX, newY);
}

void Bull::checkDistance()
{
	if (isAlive()) {
			int range = 300; //rango
			double dirX = getPosition().getX() - game->getPosisitionPlayer().getX(); //direccion en las x
			double dirY = getPosition().getY() - game->getPosisitionPlayer().getY(); //direccion en las y
			double distanceX = abs(dirX); //distancia en valor absoluto en las x
			double distanceY = abs(dirY); //distacia en valor absoluto en las y

			//Si esta en el rango
			if (distanceX <= range && distanceY <= range) //Si esta en el rango
			{
				stop = false; //Dejo de patrullar
				timer_ = SDL_GetTicks();
				chase(dirX, dirY); //Persigo

				sdlutils().soundEffects().at("bull").setVolume(game->getSoundEfectsVolume());
				sdlutils().soundEffects().at("bull").play(0, 1);


			}
			else if (SDL_GetTicks() <= timer_ + 3000) //Si no esta en el rango y no han pasado los 3 segundos 
				chase(dirX, dirY); //Persigo

			else  //Si no esta en el rango y han pasado los 3 segundos
				stop = true; //Dejo de perseguir
	}

}

void Bull::draw()
{
	if (isAlive()) {
		if (collided && (game->getPlayer()->isUsingFlashLight() || game->getPlayer()->isUsingLantern())) {
			setTexture(bullDyingSpritesheet);
			animationManager->getFrameImageBull(getCollider(), textureRect, texture, timerAnimation);
		}
		else {
			setTexture(bullspritesheet);
			animationManager->getFrameImageBull(getCollider(), textureRect, texture, timerAnimation);
		}
	}
}

void Bull::bullScares()
{
	if (isAlive()) {
		if (lastUpdate_ + 1000 < SDL_GetTicks()) {
			int offset = 300;
			double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX());
			double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

			if (distanceX <= offset && distanceY <= offset) {

				/*if (distanceX < distanceY)
					game->scare(distanceX*scariness_);
				else*/

				double d = 1.8 * ((distanceY + distanceX) / 2);
				if (distanceX <= 20.0 && distanceY <= 20.0) {
					game->scare(2.0 * scariness_ / 10);
				}
				//si no es demasiado por eso se divide entre 8
				else game->scare(d * scariness_ / 10);///esto hay que mirarlo
				lastUpdate_ = SDL_GetTicks();
			}
			lastUpdate_ = SDL_GetTicks();
		}
	}
}
