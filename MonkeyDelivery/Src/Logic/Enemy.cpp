#include "Enemy.h"

Enemy::Enemy(Game* game,int Aleatorio, Point2D<int>centroRadio):GameObject(game){
	zone =  SpawnZone(Aleatorio, centroRadio);
	Vector2D<double> randomPos = zone.genratePoint();
	setPosition(randomPos.getX(),randomPos.getY());
	setTexture(monkeyEyesClosedTexture);
	setAlive(true);
}

void Enemy::move(double speed)
{

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
	limitPointLeft = getX() - 100;
	limitPointRight = getY() + 100;
}

void Enemy::onCollision()
{
}

void Enemy::update()
{
}

void Enemy::draw()
{
		drawTexture(texture);
}
