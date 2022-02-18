#include "Player.h"

Player::Player(Game* game) :GameObject(game) {
	this->game = game;
	texture = nullptr;
	setTexture(monkeyTexture);

	fear_ = 0;
	money_ = 0;
	walkingSpeed_ = 3;
	runningSpeed_ = 5;
	walkingEnergy_ = 2;

	setPosition(15, 100);
	setDimension(100, 100);

	energyLevel_ = new energyLevel(game);
}

Player::~Player()
{
	delete energyLevel_;
	energyLevel_ = nullptr;
}

void Player::update()
{
}

/// <summary>
/// Se le suma a la pos la x y la y del parametro
/// </summary>
/// <param name="speed"> La primera componente es la x y la segunda la y</param>
void Player::move(pair<double, double> speed)
{
	setPosition(getX() + speed.first*walkingSpeed_, getY() + speed.second*walkingSpeed_);
	drainEnergy(walkingEnergy_);

	//cout << "POSICION PLAYER:" << getX() << "," << getY() << endl;
	//cout << "POSICION BARRA:" << energyLevel_->getX() << "," << energyLevel_->getY() << endl;
	
}

void Player::sleep()
{
}

void Player::getScared(int amount)
{
}

/// <summary>
/// Contador para bajar cada maxCont_ amout a energy_
/// </summary>
/// <param name="amount"> cantidad que se le va añadir a energy_
void Player::drainEnergy(int amount)
{
	energyLevel_->drain(amount);
}

void Player::recoverEnergy(int amount)
{
}

void Player::recoverFear(int amount)
{
}

void Player::getMoney(int amount)
{
	money_ += amount;
}

void Player::removeMoney(int amount)
{
	money_ -= amount;
}

void Player::draw()
{
	drawTexture(texture);
	drawDebug();
	energyLevel_->draw();
	energyLevel_->drawDebug();

}
