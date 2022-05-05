#include "Enemy.h"
#include "../Logic/Game.h"

Enemy::Enemy(Game* game, int radio, Point2D<int>centroRadio) : GameObject(game, true) {

	zone = SpawnZone(radio, centroRadio); //Creaccion de la zona de spawn
	setAlive(true);
	indexCheckPoint = 0;
	back = false; //Boolenao que indica cuando se da la vuelta el enemigo en su patrulla
	timerAnimation_ = 0;
	lastUpdate_ = SDL_GetTicks();
	timeOnFlash_ = SDL_GetTicks();
	respawnTimer = SDL_GetTicks();
	nearLimit_ = 2;
	timeLimit_ = 250;
	setMaxFearPercent(30);
	popupTexture = game->getTexture(fearPopUp);
	popUpTexRect = {0, 0, 22, 12};
	popUpActive = false;
	popUpTimer = 160;
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
				indexCheckPoint = (int)checkpoints.size() - 1;
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
			game->getPlayer()->addMoney(deathReward_);
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
			game->getPlayer()->addMoney(deathReward_);
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
		if (respawnTimer + 210000 < SDL_GetTicks()) {
			spawn();
			respawnTimer = SDL_GetTicks();
		}
	}
}

void Enemy::checkDistance()
{
	if (isAlive()) {
		int range = 300;
		double dirX = getPosition().getX() - game->getPosisitionPlayer().getX(); //direccion en las x
		double distanceX = abs(dirX);
		double distanceY = abs(getPosition().getY() - game->getPosisitionPlayer().getY());

		double shouldFlip = getPosition().getX() - game->getPosisitionPlayer().getX();
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
		
		if (distanceX <= range && distanceY <= range) {
			//flip
			if (dirX < 0) setFlip(SDL_FLIP_HORIZONTAL);
			else setFlip(SDL_FLIP_NONE);
			//miedo
			if (lastUpdate_ + timeLimit_ < SDL_GetTicks()) {
				double minDis = min(distanceX, distanceY);
				setScariness(range / (minDis * 3));
				if (scariness_ > maxFearPercent_) setScariness(maxFearPercent_); //Como mximo quita un 25% cada vez
				game->scare(scariness_);
				lastUpdate_ = SDL_GetTicks();
			}
			popUpActive = true;
		}
		else popUpActive = false;
	}
}

void Enemy::drawPopUp()
{
	if (!popUpActive) return;

	auto pos = getCollider();
	pos.x -= (int)game->getCamera()->getCameraPosition().getX() - 10;
	pos.y -= (int)game->getCamera()->getCameraPosition().getY() - 15;

	SDL_Rect oRect = { pos.x, pos.y, 21 * 3, 12 * 3};
	animationManager->getFrameImage(oRect, popUpTexRect, popupTexture, popUpTimer, SDL_FLIP_NONE, 22*3, 12*3, 154, 1, time_);
}

bool Enemy::inPoint()
{
	auto point = checkpoints[indexCheckPoint] + offsetCamera;
	double x = getPosition().getX() - point.getX(),
		y = getPosition().getY() - point.getY();

	return abs((int)x) + abs((int)y) < nearLimit_;
}