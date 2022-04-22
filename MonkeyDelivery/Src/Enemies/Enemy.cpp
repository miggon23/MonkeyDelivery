#include "Enemy.h"
#include "../Logic/Game.h"

Enemy::Enemy(Game* game, int radio, Point2D<int>centroRadio, AnimationManager* animation) : GameObject(game, true), animationManager(animation) {

	zone = SpawnZone(radio, centroRadio); //Creaccion de la zona de spawn
	setAlive(true);
	indexCheckPoint = 0;
	back = false; //Boolenao que indica cuando se da la vuelta el enemigo en su patrulla
	timerAnimation = 0;
	lastUpdate_ = SDL_GetTicks();
	timeOnFlash_ = SDL_GetTicks();
	respawnTimer = SDL_GetTicks();
	nearLimit_ = 2;
}

void Enemy::patrol(double speed)
{
	if (checkpoints.size() > 1)
	{
		//añadido el offset de la camara a cada punto
		auto point = checkpoints[indexCheckPoint] + offsetCamera;
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
		if (inPoint()) {
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
		}
	}
}

void Enemy::die()
{
	if (game->getPlayer()->isUsingFlashLight()) {
		
		// se guardan los ticks al colisionar con la luz
		if (collide(game->getPlayer()->lightZoneFL()) && !collided) {
			collided = true;
			timeOnFlash_ = SDL_GetTicks();
		}
		// si se sale del collider de la luz se resetea todo 
		//para que no se muera el enemigo al segundo hit
		if (!collide(game->getPlayer()->lightZoneFL()) && collided) {
			collided = false;
		}
		// si pasa Xs en la luz, se muere
		if (timeOnFlash_ + resistence_ < SDL_GetTicks() && collide(game->getPlayer()->lightZoneFL()) && collided) {
			setAlive(false);
			collided = false;
		}
	}

	if (game->getPlayer()->isUsingLantern()) {

		// se guardan los ticks al colisionar con la luz
		if (collide(game->getPlayer()->lightZoneL()) && !collided) 
		{
			collided = true;
			timeOnFlash_ = SDL_GetTicks();
		}
		// si se sale del collider de la luz se resetea todo 
		//para que no se muera el enemigo al segundo hit
		if (!collide(game->getPlayer()->lightZoneL()) && collided) {
			collided = false;
		}
		// si pasa Xs en la luz, se muere
		if (timeOnFlash_ + resistence_ < SDL_GetTicks() && collide(game->getPlayer()->lightZoneL()) && collided) {
			setAlive(false);
			collided = false;
		}
	}
}

void Enemy::spawn()
{
	setAlive(true); //Para que cuando reaparezca este vivo
	Vector2D<double> randomPos = zone.generatePoint();
	setPosition(randomPos.getX(), randomPos.getY());
}


void Enemy::respawn()
{
	if (!isAlive()) {
		if (!startTimer) {
			respawnTimer = SDL_GetTicks();
			startTimer = true;
		}
		if (respawnTimer + 15000 < SDL_GetTicks()) {
			spawn();
			respawnTimer = SDL_GetTicks();
		}
	}
}

void Enemy::checkDistance()
{
	if (isAlive()) {
		int range = 300;
		double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX());
		double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

		if (distanceX <= range && distanceY <= range) {

			if (lastUpdate_ + 1500 < SDL_GetTicks()) {
				double minDis = min(distanceX, distanceY);
				scariness_ = range / (minDis * 3);
				if (scariness_ > 20) scariness_ = 20; //Como mximo quita un 20% cada vez
				game->scare(scariness_);
				lastUpdate_ = SDL_GetTicks();
				//cout << "MIEDO: " << scariness_ << endl;
			}
		}
	}
}

bool Enemy::inPoint()
{
	auto point = checkpoints[indexCheckPoint] + offsetCamera;
	int x = getPosition().getX() - point.getX(),
		y = getPosition().getY() - point.getY();

	return abs(x) + abs(y) < nearLimit_;
}