#include "Scorpion.h"
#include "../Logic/Game.h"

Scorpion::Scorpion(Game* game, int Aleatorio, Point2D<int> centroRadio, AnimationManager* animation) : Enemy(game, Aleatorio, centroRadio, animation)
{
	setTexture(scorpionSS_Default);
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setDimension(60, 60);
	initialPos_ = getPosition();
	createCheckPoints();
	lastUpdate_ = SDL_GetTicks();
	iniPlayerVel = game->getPlayer()->getVel();
	inRange = false;
	setResistance(2500);
	setMaxFearPercent(50);
	width_ = height_ = 18;
	time_ = 200;
	maxX_ = 144;
	maxY_ = 0;
	textureRect = { 0, 0, width_, height_ };
}

void Scorpion::update()
{
	patrol(1);
	checkDistance();
	die();
	respawn();
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
	int range = 120; //rango
	double dirX = getPosition().getX() - game->getPosisitionPlayer().getX(); //direccion en las x
	double distanceX = abs(dirX); //distancia en valor absoluto en las x
	double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY()); //distacia en valor absoluto en las y

	double playerVel = game->getPlayer()->getVel();

	//Si esta en el rango
	if (distanceX <= range && distanceY <= range)
	{
		//flip
		if (dirX > 0) setFlip(SDL_FLIP_HORIZONTAL);
		else setFlip(SDL_FLIP_NONE);

		//Si la velocidad del jugador no ha sido reducida, es decir, no había entrado en el rango
		if (!inRange) { 
			game->setVel(playerVel / 2.0);
			sdlutils().soundEffects().at("scorpion").setVolume((int)(game->getSoundEfectsVolume() * game->getGeneralVolume()));
			sdlutils().soundEffects().at("scorpion").play(0, 1);
			inRange = true;
		}
		if (lastUpdate_ + timeLimit_ < SDL_GetTicks()) {
			double minDis = min(distanceX, distanceY);
			setScariness(range / (minDis * 3));
			if (scariness_ > maxFearPercent_) setScariness(maxFearPercent_); //Como mximo quita un 25% cada vez
			game->scare(scariness_);
			lastUpdate_ = SDL_GetTicks();
		}
	}
	//Si no esta en el rango la velocidad sera normal
	else if (inRange) //<-- En rango aún
	{
		game->getPlayer()->setVel(playerVel * 2.0);
		inRange = false;
	}
}

void Scorpion::draw()
{
	if (isAlive()) {
		auto pos = getCollider();
		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();
		if (collided && (game->getPlayer()->isUsingFlashLight() || game->getPlayer()->isUsingLantern())) 
			setTexture(scorpionSS_Death);
		
		else setTexture(scorpionSS_Default);
		
		animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
	}
}