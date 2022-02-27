#include "FearLevel.h"

FearLevel::FearLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	fear_ = 0;
	maxFear_ = 100;
	setTexture(energyLevelTexture);
	setPosition(place_, 10);
	setDimension(200, 20);
}

// Drena energía y devuelve true si se queda a 0
bool FearLevel::drain(float energyDrained)
{
	fear_ -= energyDrained;
	if (fear_ > 0) {
		setDimension(fear_, 20);
		setPosition(50 - (energyDrained/2), 10);
		return false;
	}
	else {
		// avisa al player de que está sin energía
		//cout << "ME DUERMO" << endl;
		return true;
	}
}


void FearLevel::draw()
{
	drawTexture(texture);
}
