#include "Enemy.h"
#include "Game.h"

<<<<<<< HEAD
Enemy::Enemy(Game* game, int radio, Point2D<int>centroRadio, AnimationManager* animation) : GameObject(game, true), animationManager(animation) {

	zone = SpawnZone(radio, centroRadio); //Creaccion de la zona de spawn
=======
Enemy::Enemy(Game* game, int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation) : GameObject(game), animationManager(animation) {

	zone = SpawnZone(Aleatorio, centroRadio); //Creaccion de la zona de spawn
>>>>>>> Visuals_Revamp
	setAlive(true);
	indexCheckPoint = 0;
	back = false; //Boolenao que indica cuando se da la vuelta el enemigo en su patrulla
	timerAnimation = 0;
	lastUpdate_ = SDL_GetTicks();
	timeOnFlash_ = SDL_GetTicks();
<<<<<<< HEAD
	respawnTimer = SDL_GetTicks();
=======
	//setScariness(0.7);

>>>>>>> Visuals_Revamp
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
<<<<<<< HEAD
=======
			//std::cout << indexCheckPoint << std::endl;
>>>>>>> Visuals_Revamp
		}
	}
}

void Enemy::die()
{
<<<<<<< HEAD
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
		if (collide(game->getPlayer()->lightZoneL()) && !collided) {
=======
	if (game->getPlayer()->usingFlashLight) {

		// se guardan los ticks al colisionar con la luz
		if (collide(game->getPlayer()->lightZone()) && !collided) {
>>>>>>> Visuals_Revamp
			collided = true;
			timeOnFlash_ = SDL_GetTicks();
		}
		// si se sale del collider de la luz se resetea todo 
		//para que no se muera el enemigo al segundo hit
<<<<<<< HEAD
		if (!collide(game->getPlayer()->lightZoneL()) && collided) {
			collided = false;
		}
		// si pasa Xs en la luz, se muere
		if (timeOnFlash_ + resistence_ < SDL_GetTicks() && collide(game->getPlayer()->lightZoneL()) && collided) {
			setAlive(false);
=======
		if (!collide(game->getPlayer()->lightZone()) && collided) {
			collided = false;
		}
		// si pasa Xs en la luz, se muere
		if (timeOnFlash_ + resistence_ < SDL_GetTicks() && collide(game->getPlayer()->lightZone()) && collided) {
			setAlive(false);
			hasBeenKilled = true;
>>>>>>> Visuals_Revamp
			collided = false;
		}
	}
}
<<<<<<< HEAD
=======

>>>>>>> Visuals_Revamp
void Enemy::spawn()
{
	setAlive(true); //Para que cuando reaparezca este vivo
	Vector2D<double> randomPos = zone.generatePoint();
	setPosition(randomPos.getX(), randomPos.getY());
}

<<<<<<< HEAD
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
=======
void Enemy::onCollision()
{

>>>>>>> Visuals_Revamp
}

void Enemy::checkDistance()
{
	if (isAlive()) {
		if (lastUpdate_ + 1000 < SDL_GetTicks()) {
			int offset = 300;
			double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX());
			double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

			if (distanceX <= offset && distanceY <= offset) {

<<<<<<< HEAD
				double d = 1.8 * ((distanceY + distanceX) / 2);
=======
				/*if (distanceX < distanceY)
					game->scare(distanceX*scariness_);
				else*/

				double d = 1.8*((distanceY + distanceX) / 2);
>>>>>>> Visuals_Revamp
				if (distanceX <= 20.0 && distanceY <= 20.0) {
					game->scare(2.0 * scariness_ / 10);
				}
				//si no es demasiado por eso se divide entre 8
				else game->scare(d * scariness_ / 10);///esto hay que mirarlo
				lastUpdate_ = SDL_GetTicks();
			}
			lastUpdate_ = SDL_GetTicks();
		}
	}
<<<<<<< HEAD
=======

>>>>>>> Visuals_Revamp
}

bool Enemy::inPoint()
{
	auto point = checkpoints[indexCheckPoint] + offsetCamera;
	int x = getPosition().getX() - point.getX(),
		y = getPosition().getY() - point.getY();

	return abs(x) + abs(y) < nearLimit_;
<<<<<<< HEAD
}
=======

}

>>>>>>> Visuals_Revamp
