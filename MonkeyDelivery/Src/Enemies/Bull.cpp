#include "Bull.h"
#include "../Logic/Game.h"

Bull::Bull(Game* game, int radio, Point2D<int> centroRadio) : Enemy(game, radio, centroRadio)
{
	setTexture(bullSS_Default);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(100, 112);
	initialPos_ = getPosition();
	createCheckPoints();
	lastUpdate_ = SDL_GetTicks();
	stop = true; //Patrulla y no persigue
	setResistance(1500);
	setMaxFearPercent(25);
	width_ = 25;
	height_ = 28;
	time_ = 200;
	maxX_ = 100;
	maxY_ = 0;
	textureRect = { 0, 0, width_, height_ };
}

void Bull::update()
{
	if (stop) patrol(1); //El toro solo patrulla si no persigue 
	checkDistance();
	die();
	respawn();
	//Si han pasado 3 segundos y el toro esta persiguiendo
	if (!stop && (int)SDL_GetTicks() > timer_ + 3000) {
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
		if (distanceX <= range && distanceY <= range && game->getPlayer()->safeDistance()) //Si esta en el rango, pero player no esta en cama
		{
			stop = false; //Dejo de patrullar
			timer_ = SDL_GetTicks();
			chase(dirX, dirY); //Persigo

			sdlutils().soundEffects().at("bull").setVolume((int)(game->getSoundEfectsVolume() * game->getGeneralVolume()));
			sdlutils().soundEffects().at("bull").play(0, 1);

			if (lastUpdate_ + timeLimit_ < SDL_GetTicks()) {
				double minDis = min(distanceX, distanceY);
				setScariness(range / (minDis * 3));
				if (scariness_ > maxFearPercent_) setScariness(maxFearPercent_); //Como mximo quita un 10% cada vez
				game->scare(scariness_/2);
				lastUpdate_ = SDL_GetTicks();
			}
		}
		else if ((int)SDL_GetTicks() <= timer_ + 3000 && game->getPlayer()->safeDistance()) //Si no esta en el rango y no han pasado los 3 segundos, pero player no esta en cama
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
		
		animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
	}
}