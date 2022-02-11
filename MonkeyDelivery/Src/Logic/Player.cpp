#include "Player.h"
Player::Player(Game* game) :GameObject(game) {
	texture = nullptr;
	setTexture(monkeyTexture);
}

void Player::Move(double speed)
{
}

void Player::Sleep()
{
}

void Player::GetScared(int amount)
{
}

void Player::DrainEnergy(int amount)
{
}

void Player::RecoverEnergy(int amount)
{
}

void Player::RecoverFear(int amount)
{
}
