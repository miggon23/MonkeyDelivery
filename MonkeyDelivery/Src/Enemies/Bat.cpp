#include "Bat.h"
#include "../Logic/Game.h"

Bat::Bat(Game* game, int Aleatorio, Point2D<int> centroRadio, int nLoop) : Enemy(game, Aleatorio, centroRadio)
{
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setTexture(batSS_Default);
	setDimension(105, 90);
	initialPos = getPosition();
	stealTimer_ = SDL_GetTicks();
	speed_ = 1;
	player_ = game->getPlayer();
	loops = nLoop;
	width_ = 35;
	height_ = 30;
	time_ = 250;
	maxX_ = 70;
	maxY_ = 0;
	textureRect = { 0, 0, width_, height_ };
	
	createCheckPoints();
	setResistance(2000);
}

void Bat::update()
{
	patrol(speed_);

	SDL_Rect r1 = player_->getCollider();
	SDL_Rect r2 = this->getCollider();

	if (SDL_HasIntersection(&r2, &r1))
	{
		onPlayerInteraction(player_);
	}

	checkDistance();
	die();
	respawn();
}

void Bat::createCheckPoints()
{
	int move = 10;

	addCheckPoint(initialPos);
	addCheckPoint(Point2D<double>(initialPos.getX() + 100, initialPos.getY() - 100));
	addCheckPoint(Point2D<double>(initialPos.getX(), initialPos.getY() - 200));
	addCheckPoint(Point2D<double>(initialPos.getX() - 100, initialPos.getY() - 100));
	addCheckPoint(Point2D<double>(initialPos.getX(), initialPos.getY()));

	for (int i = 1; i < loops; i++)
	{
		addCheckPoint(Point2D<double>(initialPos.getX() + (double) move * i, initialPos.getY()));
		addCheckPoint(Point2D<double>(initialPos.getX() + 100 + (double) move * i, initialPos.getY() - 100));
		addCheckPoint(Point2D<double>(initialPos.getX() + (double) move * i, initialPos.getY() - 200));
		addCheckPoint(Point2D<double>(initialPos.getX() - 100 + (double) move * i, initialPos.getY() - 100));
		addCheckPoint(Point2D<double>(initialPos.getX() + (double) move * i, initialPos.getY()));
	}
}

void Bat::onPlayerInteraction(Player* player)
{
	if (isAlive()) {
		if (stealTimer_ + 750 < SDL_GetTicks()) {
			player->removeMoney(1);

			sdlutils().soundEffects().at("bat").setVolume((int)(game->getSoundEfectsVolume() * game->getGeneralVolume()));
			sdlutils().soundEffects().at("bat").play(0, 1);
			stealTimer_ = SDL_GetTicks();
		}
	}
}

void Bat::draw(){
	if (isAlive()) {
		auto pos = getCollider();
		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();
		if (collided && (game->getPlayer()->isUsingFlashLight() || game->getPlayer()->isUsingLantern())) 
			setTexture(batSS_Death);
		
		else 
			setTexture(batSS_Default);
		
		animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
	}
}