#include "Player.h"

Player::Player(Game* game) :GameObject(game) {
	this->game = game;
	texture = nullptr;
	setTexture(monkeyTexture);
	maxEnergy_ = 80;
	energy_ = maxEnergy_;
	fear_ = 0;
	money_ = 0;
	walkingSpeed_ = 3;
	runningSpeed_ = 5;
	cont_ = 1;
	maxCont_ = 2;
	isMoving_ = 2;
	setPosition(100, 100);
	setDimension(100, 100);
	energyLevel_ = new energyLevel(game);
}

Player::~Player()
{
	energyLevel_ = nullptr;
	delete energyLevel_;
}

void Player::update()
{
	drainEnergy(-1);
	energyLevel_->draw();
	energyLevel_->changeWidth( (maxEnergy_ - energy_)*2 );

}

/// <summary>
/// Se le suma a la pos la x y la y del parametro
/// </summary>
/// <param name="speed"> La primera componente es la x y la segunda la y</param>
void Player::move(pair<double, double> speed)
{
	setPosition(getX() + speed.first*walkingSpeed_, getY() + speed.second*walkingSpeed_);
	drainEnergy(-isMoving_);
	//cout << "POSICION:" << getX() << "," << getY() << endl;
	
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
	cont_ += 1;

	if (cont_ == maxCont_ && energy_ != 0) {
		energy_ += amount;
		cont_ = 1;
	}
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
}