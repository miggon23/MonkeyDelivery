#include "energyLevel.h"
#include "..\Logic\Game.h"

energyLevel::energyLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	energy_ = 168;
	maxEnergy_ = 100;
	setTexture(UI_energyLevel);
	

	x = (int)(game->getWindowWidth() / 7.5);
	y = (int)(game->getWindowHeight() / 23);
	h = (int)(game->getWindowHeight() / 60);

	scale_ = (1.76 / 1800) * game->getWindowWidth();

	setPosition(x, y);
	setDimension(100*scale_, h);
}

// Drena energía y devuelve true si se queda a 0
bool energyLevel::drain(double energyDrained){

	energy_ -= energyDrained;
	if (energy_ > maxEnergy_)
		energy_ = maxEnergy_;
	if (energy_ > 0) {
		setDimension((energy_) * scale_, h);
		setPosition(x - (energyDrained / 2), y);
		return false;
	}
	else {
		energy_ = 0;
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
