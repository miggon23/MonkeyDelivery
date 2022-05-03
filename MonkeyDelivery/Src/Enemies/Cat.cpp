#include "Cat.h"
#include "../Logic/Game.h"
#include <cmath>
#include <algorithm>

Cat::Cat(Game* game,int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation):Enemy(game, Aleatorio, centroRadio, animation){

	Vector2D<double> zonePoint = zone.generatePoint(); //genera un punto en la zona de spawn
	setPosition(zonePoint.getX(), zonePoint.getY()); //Coloca al enemigo en ese punto
	initialPos = getPosition();
	setTexture(catSS_Default);
	setDimension(52, 70);
	createCheckPoints();
	setResistance(1000);
	setMaxFearPercent(45);
	width_ = 16;
	height_ = 20;
	time_ = 250;
	maxX_ = 64;
	maxY_ = 0;
	textureRect = { 0, 0, width_, height_ };
}

void Cat::update()
{
	patrol(1);
	checkDistance();
	die();
	respawn();
}

void Cat::createCheckPoints()
{
	double offset = 30.0;

	addCheckPoint(initialPos);
	addCheckPoint(Point2D<double>(initialPos.getX() + offset, initialPos.getY() - offset));
	addCheckPoint(Point2D<double>(initialPos.getX(), initialPos.getY() - offset*2));
	addCheckPoint(Point2D<double>(initialPos.getX() - offset, initialPos.getY() - offset));
	addCheckPoint(initialPos);
}

void Cat::draw()
{
	if (isAlive()) {
		auto pos = getCollider();
		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();
		if (collided && (game->getPlayer()->isUsingFlashLight() || game->getPlayer()->isUsingLantern())) 
			setTexture(catSS_Death);
		
		else setTexture(catSS_Default);
		
		animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
	}
}

void Cat::checkDistance()
{
	if (isAlive()) {
		
		int range = 400;
		double dirX = getPosition().getX() - game->getPosisitionPlayer().getX(); //direccion en las x
		double distanceX = abs(dirX);
		double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

		if (distanceX <= range && distanceY <= range) {
			//flip
			if (dirX < 0) setFlip(SDL_FLIP_HORIZONTAL);
			else setFlip(SDL_FLIP_NONE);
			//sonidos
			sdlutils().soundEffects().at("cat").setVolume(game->getSoundEfectsVolume() * game->getGeneralVolume());
			sdlutils().soundEffects().at("cat").play(0, 1);
			//miedo
			if (lastUpdate_ + timeLimit_ < SDL_GetTicks()) {
				double minDis = min(distanceX, distanceY);
				scariness_ = range / (minDis*3);
				if (scariness_ > maxFearPercent_) setScariness(maxFearPercent_); //Como mximo quita un 30% cada vez
				game->scare(scariness_);
				lastUpdate_ = SDL_GetTicks();
			}
		}
	}
}