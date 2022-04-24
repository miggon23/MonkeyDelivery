#include "Plant.h"
#include "../Logic/Game.h"

Plant::Plant(Game* game, int Aleatorio, Point2D<int> centroRadio, AnimationManager* animation) :Enemy(game, Aleatorio, centroRadio, animation)
{
	Vector2D<double> zonePoint = zone.generatePoint(); //genera un punto en la zona de spawn
	setPosition(zonePoint.getX(), zonePoint.getY()); //Coloca al enemigo en ese punto
	setTexture(plantSS_Default);
	setDimension(80, 90);
	setResistance(4000);
	lastUpdate_ = SDL_GetTicks();
	setScariness(0.0); //NO DA MIEDO
	textureRect = { 0, 0, animationManager->getWidthPlant(),animationManager->getHeigthPlant() };
}

void Plant::update()
{
	checkDistance();
	die();
	respawn();
}
//void Plant::die() {
//	if (game->getPlayer()->usingFlashLight) {
//		if (collide(game->getPlayer()->lightZone())) {
//			if (timeOnFlash_ + 5000 < SDL_GetTicks()) {
//				setAlive(false);
//			}
//			timeOnFlash_ = SDL_GetTicks();
//		}
//	}
//}
void Plant::checkDistance()
{
	int range = 200; //rango
	double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX()); //distancia en valor absoluto en las x
	double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY()); //distacia en valor absoluto en las y

	if (distanceX <= range && distanceY <= range) {

		game->drainPlayerEnergy(0.2);

		//Realmente esto no se si comentarlo porque la planta no da miedo, de momento lo dejo
		if (lastUpdate_ + 1000 < SDL_GetTicks())
		{
			game->scare(scariness_);
			/*sdlutils().soundEffects().at("plant").setVolume(game->getSoundEfectsVolume());
			sdlutils().soundEffects().at("plant").play(0, 1);*/

		}
		
		lastUpdate_ = SDL_GetTicks();
	}
}

void Plant::draw()
{
	if (isAlive()) {
		auto pos = getCollider();
		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();
		if (collided && (game->getPlayer()->isUsingFlashLight() || game->getPlayer()->isUsingLantern())) 
			setTexture(plantSS_Death);
		
		else 
			setTexture(plantSS_Default);
		
		animationManager->getFrameImagePlant(pos, textureRect, texture, timerAnimation);
	}
}