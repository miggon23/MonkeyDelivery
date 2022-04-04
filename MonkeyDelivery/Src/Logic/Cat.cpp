#include "Cat.h"
#include "Game.h"
Cat::Cat(Game* game,int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation):Enemy(game, Aleatorio, centroRadio, animation){

	Vector2D<double> zonePoint = zone.generatePoint(); //genera un punto en la zona de spawn
	setPosition(zonePoint.getX(), zonePoint.getY()); //Coloca al enemigo en ese punto
	initialPos = getPosition();
	setTexture(catspritesheet);
	setDimension(50, 60);
	createCheckPoints();
	setScariness(0.1);
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
		if (collided && (game->getPlayer()->isUsingFlashLight() || game->getPlayer()->isUsingLantern())) {
			setTexture(catDyingSpritesheet);
			animationManager->getFrameImageCat(getCollider(), textureRect, texture, timerAnimation);
		}
		else {
			setTexture(catspritesheet);
			animationManager->getFrameImageCat(getCollider(), textureRect, texture, timerAnimation);
		}
	}
}

void Cat::checkDistance()
{
	if (isAlive()) {
		if (lastUpdate_ + 1000 < SDL_GetTicks()) {
			int offset = 300;
			double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX());
			double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

			if (distanceX <= offset && distanceY <= offset) {
				sdlutils().soundEffects().at("cat").setVolume(game->getSoundEfectsVolume());
				sdlutils().soundEffects().at("cat").play(0, 1);

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
