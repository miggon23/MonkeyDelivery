#include "energyLevel.h"

energyLevel::energyLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	energy_ = 200;
	maxEnergy_ = 200;
	setTexture(energyLevelTexture);
	setPosition(20, 20);
	setDimension(111*4, 39*4);
}

// Drena energía y devuelve true si se queda a 0
bool energyLevel::drain(float energyDrained)
{
	energy_ -= energyDrained;
	//if (energy_ > maxEnergy_)energy_ = maxEnergy_;
	//if (energy_ > 0) {
	//	setDimension(energy_, 50);
	//	setPosition(50 - (energyDrained/2), 10);
	//	return false;
	//}
	//else {
	//	energy_ = 0;
	//	// avisa al player de que está sin energía
	//	//cout << "ME DUERMO" << endl;
	//	return true;
	//}
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
