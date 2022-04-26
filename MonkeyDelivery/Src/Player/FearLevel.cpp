#include "FearLevel.h"

FearLevel::FearLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	fear_ = 0;
	maxFear_ = 100;
	setTexture(UI_fearLevel);
	setPosition(55*4 + 20, 15*4 + 20);
	setDimension(6*4, 0);
}

//se asusta y si llega a 100 se desmaya
bool FearLevel::getScared(double amount)
{
	fear_+= amount;
	if (fear_ < 0) fear_ = 0;
	else if (fear_ > maxFear_) fear_ = maxFear_;
	if (fear_ < maxFear_) {
		setDimension(fear_*1.68, 50);
		setPosition(55 * 4 + 20 - (amount/2), 15 * 4 + 20);
		return false;
	}
	else {
		/* avisa al player de que está sin energía
		cout << "ME DESMAYO SOY UN CAGUETA" << endl;*/
		return true;
	}
}

void FearLevel::resetFear()
{
	fear_ = 0;
	getScared(fear_);
}

void FearLevel::draw()
{
	drawTexture(texture);
}