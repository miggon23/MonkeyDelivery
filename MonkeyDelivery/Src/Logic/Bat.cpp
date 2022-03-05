#include "Bat.h"
#include "Game.h"

Bat::Bat(Game* game, int Aleatorio, Point2D<int> centroRadio, int nLoop) : Enemy(game, Aleatorio, centroRadio)
{
	Vector2D<double> zonePoint = zone.generatePoint();
	setPosition(zonePoint.getX(), zonePoint.getY());
	setTexture(batTexture);
	setDimension(90, 100);
	initialPos = getPosition();
	
	speed = 1;
	player_ = game->getPlayer();
	
	loops = nLoop;

	createCheckPoints();
}

void Bat::update()
{
	move(speed);

	SDL_Rect r1 = player_->getCollider();
	SDL_Rect r2 = this->getCollider();

	if (SDL_HasIntersection(&r2, &r1))
	{
		onPlayerInteraction(player_);
	}

	checkDistance();
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
	player->removeMoney(1);
}
