#include "Plant.h"
#include "../Logic/Game.h"

Plant::Plant(Game* game, int Aleatorio, Point2D<int> centroRadio, AnimationManager* animation) :Enemy(game, Aleatorio, centroRadio, animation )
{
	Vector2D<double> zonePoint = zone.generatePoint(); //genera un punto en la zona de spawn
	setPosition(zonePoint.getX(), zonePoint.getY()); //Coloca al enemigo en ese punto
	
	//EJEJEJE le pone una textura aleatoria a la planta entre los cuatro colores que hay
	//totalmente irrelevante pero queda bonito y es mas divertido que arreglar el juego 
	//Jacobo :D
	int randomInt = sdlutils().rand().nextInt(0,4);
	switch (randomInt)
	{
		case 0: randomTex = plantSS_Yellow; break;
		case 1: randomTex = plantSS_Red; break;
		case 2: randomTex = plantSS_Purple; break;
		case 3: randomTex = plantSS_Orange; break;
	}
	setTexture(randomTex);
	setDimension(100, 100);
	setResistance(4000);
	lastUpdate_ = SDL_GetTicks();
	setScariness(0.0); //NO DA MIEDO
	width_ = height_ = 28;
	time_ = 350;
	maxX_ = 56;
	maxY_ = 0;
	textureRect = { 0, 0, width_, height_ };
}

void Plant::update()
{
	checkDistance();
	die();
	respawn();
}

void Plant::checkDistance()
{
	int range = 200; //rango
	double dirX = getPosition().getX() - game->getPosisitionPlayer().getX(); //direccion en las x
	double distanceX = abs(dirX); //distancia en valor absoluto en las x
	double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY()); //distacia en valor absoluto en las y

	if (distanceX <= range && distanceY <= range) {
		//flip
		if(dirX<0) setFlip(SDL_FLIP_HORIZONTAL);
		else setFlip(SDL_FLIP_NONE);

		game->drainPlayerEnergy(0.2);

		//Realmente esto no se si comentarlo porque la planta no da miedo, de momento lo dejo
		if (lastUpdate_ + timeLimit_ < SDL_GetTicks())
		{
			game->scare(scariness_);
			sdlutils().soundEffects().at("plant").setVolume((int)(game->getSoundEfectsVolume() * game->getGeneralVolume()));
			sdlutils().soundEffects().at("plant").play(0, 1);
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
			setTexture(randomTex);
		
		animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
	}
}