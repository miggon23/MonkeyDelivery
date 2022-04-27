#include "energyLevel.h"

energyLevel::energyLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	energy_ = 168;
	maxEnergy_ = 100;
	setTexture(UI_energyLevel);
	setPosition(55*4 + 20, 5*4 + 20);
	setDimension(42*4, 6*4);
}

// Drena energía y devuelve true si se queda a 0
bool energyLevel::drain(double energyDrained){
	energy_ -= energyDrained;
	cout << energy_ << endl;
	if (energy_ > maxEnergy_)energy_ = maxEnergy_;
	if (energy_ > 0) {
		setDimension((energy_)*1.68, 6*4);
		setPosition(55 * 4 + 20 - (energyDrained/2), 5 * 4 + 20);
		return false;
	}
	else {
		energy_ = 0;
		// avisa al player de que está sin energía
		//cout << "ME DUERMO" << endl;
		return true;
	}
	return true;
}

void energyLevel::resetEnergy()
{
	energy_ = maxEnergy_;
}

void energyLevel::draw()
{
	drawTexture(texture);
}
