#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game, int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation) : GameObject(game), animationManager(animation) {

	zone = SpawnZone(Aleatorio, centroRadio); //Creaccion de la zona de spawn
	setAlive(true);
	indexCheckPoint = 0;
	back = false; //Boolenao que indica cuando se da la vuelta el enemigo en su patrulla
	timerAnimation = 0;
	lastUpdate_ = SDL_GetTicks(); 
	timeOnFlash_ = SDL_GetTicks();
	//setScariness(0.7);
}

void Enemy::patrol(double speed)
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
	if (game->getPlayer()->usingFlashLight) {
		if (collide(game->getPlayer()->lightZone()) && !collided) {
			collided = true;
			timeOnFlash_ = SDL_GetTicks();
		}
		if (timeOnFlash_ + 5000 < SDL_GetTicks() && collide(game->getPlayer()->lightZone())) {
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

void Enemy::onCollision()
{

}

void Enemy::checkDistance()
{
	if (lastUpdate_ + 1000 < SDL_GetTicks()) {
		int offset = 300;
		double distanceX = abs(getPosition().getX() - game->getPosisitionPlayer().getX());
		double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());


		if (distanceX <= offset && distanceY <= offset) {

			/*if (distanceX < distanceY)
				game->scare(distanceX*scariness_);
			else*/
			double d = (distanceY + distanceX) / 2;

			//si no es demasiado por eso se divide entre 8
			game->scare(d * scariness_ / 10);///esto hay que mirarlo
			lastUpdate_ = SDL_GetTicks();
		}
		lastUpdate_ = SDL_GetTicks();
	}


}

