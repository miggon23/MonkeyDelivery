#include "energyLevel.h"

energyLevel::energyLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	energy_ = 200;
	maxEnergy_ = 200;
	setTexture(energyLevelTexture);
	setPosition(place_, 10);
	setDimension(200, 20);
}

// Drena energía y devuelve true si se queda a 0
bool energyLevel::drain(float energyDrained)
{
	energy_ -= energyDrained;
	if (energy_ > 0) {
		setDimension(energy_, 20);
		setPosition(50 - (energyDrained/2), 10);
		return false;
	}
	else {
		// avisa al player de que está sin energía
		cout << "ME DUERMO" << endl;
		return true;
	}
}


void energyLevel::draw()
{
	drawTexture(texture);
}
