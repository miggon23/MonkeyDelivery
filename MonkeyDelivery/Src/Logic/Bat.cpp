#include "Bat.h"
#include "Game.h"

Bat::Bat(Game* game, int Aleatorio, Point2D<int> centroRadio, int nLoop, AnimationManager* animation) : Enemy(game, Aleatorio, centroRadio,animation)
{
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setTexture(batspritesheet);
	setDimension(90, 100);
	initialPos = getPosition();
	
	speed = 1;
	player_ = game->getPlayer();
	
	loops = nLoop;
	textureRect = { 0,0,animationManager->getWidthBat(),animationManager->getHeightBat() };
	createCheckPoints();
	setResistance(2000);
}

void Bat::update()
{
	patrol(speed);

	SDL_Rect r1 = player_->getCollider();
	SDL_Rect r2 = this->getCollider();

	if (SDL_HasIntersection(&r2, &r1))
	{
		onPlayerInteraction(player_);
	}

	checkDistance();
	die();
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
		addCheckPoint(Point2D<double>(initialPos.getX() + move * i, initialPos.getY()));
		addCheckPoint(Point2D<double>(initialPos.getX() + 100 + move * i, initialPos.getY() - 100));
		addCheckPoint(Point2D<double>(initialPos.getX() + move * i, initialPos.getY() - 200));
		addCheckPoint(Point2D<double>(initialPos.getX() - 100 + move * i, initialPos.getY() - 100));
		addCheckPoint(Point2D<double>(initialPos.getX() + move * i, initialPos.getY()));

	}
}

void Bat::onPlayerInteraction(Player* player)
{
	if (isAlive()) {
		player->removeMoney(1);
	}
}

void Bat::draw(){
	if (isAlive())
	animationManager->getFrameImageBat(getCollider(), textureRect, texture,timerAnimation);
}