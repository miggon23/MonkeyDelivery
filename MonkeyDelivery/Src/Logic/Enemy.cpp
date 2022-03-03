#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game,int Aleatorio, Point2D<int>centroRadio):GameObject(game){
	zone = SpawnZone(Aleatorio, centroRadio);
	Vector2D<double> x = zone.genratePoint();
	
	setPosition(x.getX(), x.getY());
	setAlive(true);
	indexCheckPoint = 0;
	addCheckPoint(getPosition());
	back = false;
	//setScariness(0.7);
}

void Enemy::move(double speed)
{
	if (checkpoints.size() > 1)
	{
		auto point = checkpoints[indexCheckPoint];
		auto x = getPosition().getX(), y = getPosition().getY();

		if (point.getX() - x != 0) {
			if (point.getX() - x > 0)x += speed;
			else x--;
		}
		if (point.getY() - y != 0) {
			if (point.getY() - y > 0)y += speed;
			else y--;
		}
		setPosition(x, y);
		if (point == getPosition()) {
			if (back)indexCheckPoint--;
			else indexCheckPoint++;


			if (indexCheckPoint == -1) {
				indexCheckPoint = 1;
				back = false;
			}
			else if (indexCheckPoint > checkpoints.size() - 1) {
				indexCheckPoint = checkpoints.size() - 1;
				back = true;
			}
			//std::cout << indexCheckPoint << std::endl;
		}
	}
}

void Enemy::die()
{
	setAlive(false);
}

void Enemy::spawn()
{
	setAlive(true);
	Vector2D<double> randomPos = zone.genratePoint();
	setPosition(randomPos.getX(), randomPos.getY());
}

void Enemy::onCollision()
{
}

void Enemy::checkDistance()
{
	int offset = 300;
	double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX());
	double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

	if (distanceX <= offset && distanceY <= offset) {
		//std::cout << "ATACA" << std::endl;
		
		//Llamar al mtodo de quitar miedo
		/*if (distanceX < distanceY)
			game->scare(distanceX*scariness_);
		else*/
		/*double d = (distanceY + distanceX) / 2;*/
			game->scare(distanceX*scariness_);
	}
}

