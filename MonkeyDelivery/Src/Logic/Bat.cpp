#include "Bat.h"
#include "Game.h"

Bat::Bat(Game* game, int Aleatorio, Point2D<int> centroRadio, int nLoop) : Enemy(game, Aleatorio, centroRadio)
{
	setTexture(batTexture);
	speed = 1;
	player_ = game->getPlayer();
	Point2D<double> inicialPos(getPosition());
	
	addCheckPoint(Point2D<double>(inicialPos.getX(), inicialPos.getY()));
	//std::cout << inicialPos.getX() << "  " << inicialPos.getY() << endl;

	addCheckPoint(Point2D<double>(inicialPos.getX() + 100, inicialPos.getY()-100));
	std::cout << inicialPos.getX()+100 << "  " << inicialPos.getY()-100 << endl;

	addCheckPoint(Point2D<double>(inicialPos.getX(), inicialPos.getY()-200));
	std::cout << inicialPos.getX() << "  " << inicialPos.getY()-200 << endl;

	addCheckPoint(Point2D<double>(inicialPos.getX()-100, inicialPos.getY()-100));
	std::cout << inicialPos.getX()-100 << "  " << inicialPos.getY()-100 << endl;

	addCheckPoint(Point2D<double>(inicialPos.getX(), inicialPos.getY()));
	std::cout << inicialPos.getX() << "  " << inicialPos.getY() << endl;

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

}

void Bat::onPlayerInteraction(Player* player)
{
	player->removeMoney(1);

}
