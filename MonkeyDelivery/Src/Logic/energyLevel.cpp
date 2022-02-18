#include "energyLevel.h"

energyLevel::energyLevel(Game* game) :GameObject(game) {
	this->game = game;
	texture = nullptr;
	place_ = 75;
	setTexture(energyLevelTexture);
	setPosition(place_, 10);
	setDimension(250, 100);
}

void energyLevel::changeWidth(int change)
{
	setDimension(160 - change, 100);

	/*
	if (this->getX() < 75)
		place_ += 2;
	else place_ -= 2;
	*/

	setPosition(place_, 10);
}


void energyLevel::draw()
{
	drawTexture(texture);
}
