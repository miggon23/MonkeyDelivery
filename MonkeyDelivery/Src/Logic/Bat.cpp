#include "Bat.h"
#include "Game.h"

Bat::Bat(Game* game, int Aleatorio, Point2D<int> centroRadio, int nLoop) : Enemy(game, Aleatorio, centroRadio)
{
	Vector2D<double> x = zone.generatePoint();
	setPosition(x.getX(), x.getY());
	setTexture(batTexture);
	setDimension(90, 100);
	addCheckPoint(getPosition());
	speed = 1;
	player_ = game->getPlayer();
	Point2D<double> inicialPos(getPosition());
	int move = 10;
	
	addCheckPoint(Point2D<double>(inicialPos.getX(), inicialPos.getY()));
	addCheckPoint(Point2D<double>(inicialPos.getX() + 100, inicialPos.getY()-100));
	addCheckPoint(Point2D<double>(inicialPos.getX(), inicialPos.getY()-200));	
	addCheckPoint(Point2D<double>(inicialPos.getX()-100, inicialPos.getY()-100));
	addCheckPoint(Point2D<double>(inicialPos.getX(), inicialPos.getY()));

	for (int i = 1; i < nLoop; i++)
	{
		addCheckPoint(Point2D<double>(inicialPos.getX()+move*i, inicialPos.getY()));
		addCheckPoint(Point2D<double>(inicialPos.getX() + 100 + move * i, inicialPos.getY() - 100));
		addCheckPoint(Point2D<double>(inicialPos.getX() + move * i, inicialPos.getY() - 200));
		addCheckPoint(Point2D<double>(inicialPos.getX() - 100 + move * i, inicialPos.getY() - 100));
		addCheckPoint(Point2D<double>(inicialPos.getX() + move * i, inicialPos.getY()));

	}

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

void Bat::onPlayerInteraction(Player* player)
{
	player->removeMoney(1);

}
