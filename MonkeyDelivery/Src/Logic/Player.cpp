#include "Player.h"
Player::Player(Game* game) :GameObject(game) {
	this->game = game;
	texture = nullptr;
	setTexture(monkeyTexture);
	energy_ = 80;
	fear_ = 0;
	walkingSpeed_ = 3;
	runningSpeed_ = 5;
	setPosition(100, 100);
	setDimension(50, 50);
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
	cout << "POSICION:" << getX() << "," << getY() << endl;
}

void Player::sleep()
{
}

void Player::getScared(int amount)
{
}

void Player::drainEnergy(int amount)
{
}

void Player::recoverEnergy(int amount)
{
}

void Player::recoverFear(int amount)
{
}
void Player::draw()
{
	drawTexture(texture);
	cout << "simio";
}