#include "Bull.h"
#include "../Logic/Game.h"

Bull::Bull(Game* game, int radio, Point2D<int> centroRadio, AnimationManager* animation) : Enemy(game, radio, centroRadio, animation)
{
	setTexture(bullSS_Default);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(120, 120);
	initialPos_ = getPosition();
	createCheckPoints();
	lastUpdate_ = SDL_GetTicks();
	stop = true; //Patrulla y no persigue
	setResistance(1500);
	setMaxFearPercent(10);

	textureRect = { 0, 0, animationManager->getWidthBull(),animationManager->getHeigthBull() };
}

void Bull::update()
{
	if (stop) patrol(1); //El toro solo patrulla si no persigue 
	checkDistance();
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
	/*
	double newX = getPosition().getX(), newY = getPosition().getY();
	if (x < -1) newX = getPosition().getX() + speed / 2.0;		//el mono esta a la derecha
	else if (x > 1) newX = getPosition().getX() - speed / 2.0;	//el mono esta a la izquierda
	if (y < -1) newY = getPosition().getY() + speed / 2.0;		//el mono esta por debajo
	else if (y > 1) newY = getPosition().getY() - speed / 2.0;	//el mono esta por encima
	setPosition(newX, newY);
	*/
	
	Vector2D<double> newP;
	
	if (x < -1) { //el mono esta a la derecha
		newP.setX(1); 
		setFlip(SDL_FLIP_HORIZONTAL);
	}	
	else if (x > 1) { //el mono esta a la izquierda
		newP.setX(-1);
		setFlip(SDL_FLIP_NONE);
	}	
	if (y < -1) newP.setY(+1);		//el mono esta por debajo
	else if (y > 1) newP.setY(-1);	//el mono esta por encima

	newP.normalize();
	newP = getPosition() + (newP * speed);

	setPosition(newP.getX(), newP.getY());
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

			sdlutils().soundEffects().at("bull").setVolume(game->getSoundEfectsVolume() * game->getGeneralVolume());
			sdlutils().soundEffects().at("bull").play(0, 1);

			if (lastUpdate_ + timeLimit_ < SDL_GetTicks()) {
				double minDis = min(distanceX, distanceY);
				scariness_ = range / (minDis * 3);
				if (scariness_ > maxFearPercent_) setScariness(maxFearPercent_); //Como mximo quita un 10% cada vez
				game->scare(scariness_);
				lastUpdate_ = SDL_GetTicks();
			}
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
		auto pos = getCollider();
		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();
		if (collided && (game->getPlayer()->isUsingFlashLight() || game->getPlayer()->isUsingLantern())) 
			setTexture(bullSS_Death);
		
		else setTexture(bullSS_Default);
		
		animationManager->getFrameImageBull(pos, textureRect, texture, timerAnimation_, flip);
	}
}