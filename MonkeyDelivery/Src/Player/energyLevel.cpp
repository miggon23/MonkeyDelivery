#include "energyLevel.h"
#include "..\Logic\Game.h"

energyLevel::energyLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	energy_ = 168;
	maxEnergy_ = 100;
	setTexture(UI_energyLevel);
	

	x = game->getWindowWidth() / 8.18;
	y = game->getWindowHeight() / 50;
	h = game->getWindowHeight() / 38;
	setPosition(x + 20, y + 20);
	setDimension(x, h);
}

// Drena energía y devuelve true si se queda a 0
bool energyLevel::drain(double energyDrained){
	energy_ -= energyDrained;
	cout << energy_ << endl;
	if (energy_ > maxEnergy_)energy_ = maxEnergy_;
	if (energy_ > 0) {
		setDimension((energy_) * 1.68, h);
		setPosition(x + 20 - (energyDrained / 2), y + 20);
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
