#include "Enemy.h"

Enemy::Enemy(Game* game,int Aleatorio, Point2D<int>centroRadio):GameObject(game){
	zone =  SpawnZone(Aleatorio, centroRadio);
	Vector2D<double> x = zone.genratePoint();
	setPosition(x.getX(),x.getY());
	setTexture(monkeyEyesClosedTexture);
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
	Vector2D<double> x = zone.genratePoint();
	setPosition(x.getX(), x.getY());
}

void Enemy::onCollision()
{
}

void Enemy::update()
{
}

void Enemy::draw()
{
	if(alive)
		drawTexture(texture);
}
