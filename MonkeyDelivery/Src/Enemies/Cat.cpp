#include "Cat.h"
#include "../Logic/Game.h"
#include <cmath>
#include <algorithm>

Cat::Cat(Game* game,int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation):Enemy(game, Aleatorio, centroRadio, animation){

	Vector2D<double> zonePoint = zone.generatePoint(); //genera un punto en la zona de spawn
	setPosition(zonePoint.getX(), zonePoint.getY()); //Coloca al enemigo en ese punto
	initialPos = getPosition();
	setTexture(catSS_Default);
	setDimension(50, 60);
	createCheckPoints();
	setResistance(5000);
	textureRect = { 0,0,animationManager->getWidthCat(),animationManager->getHeightcat() };
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
		
		animationManager->getFrameImageCat(pos, textureRect, texture, timerAnimation);
	}
}

void Cat::checkDistance()
{
	if (isAlive()) {
		
		int range = 300;
		double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX());
		double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

		if (distanceX <= range && distanceY <= range) {
			/*sdlutils().soundEffects().at("cat").setVolume(game->getSoundEfectsVolume());
			sdlutils().soundEffects().at("cat").play(0, 1);*/
			if (lastUpdate_ + 1500 < SDL_GetTicks()) {
				double minDis = min(distanceX, distanceY);
				scariness_ = range / (minDis*3);
				if (scariness_ > 12) scariness_ = 12; //Como mximo quita un 12% cada vez
				game->scare(scariness_);
				lastUpdate_ = SDL_GetTicks();
			}
		}
	}
}