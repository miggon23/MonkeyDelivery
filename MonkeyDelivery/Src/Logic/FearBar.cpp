#include "FearBar.h"

FearBar::FearBar(Game* game) :GameObject(game) 
{
	this->game = game;
	place_ = 50;
	fear_ = 0;
	maxFear_ = 100;
	setTexture(fearLevelTexture);
	setPosition(875, 450);
	setDimension(17*3, 7*3);
}

//se asusta y si llega a 100 se desmaya
bool FearBar::getScared(int amount)
{
	/*
	fear_+= amount;
	if (fear_ < 0)fear_ = 0;
	if (fear_ <maxFear_) {
		setDimension(fear_*2, 50);
		setPosition(50 - (amount/2), 70);
		return false;
	}
	else return true;
*/
	return false;
}


void FearBar::draw()
{
	drawTexture(texture);
}
