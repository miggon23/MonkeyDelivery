#include "FearLevel.h"

FearLevel::FearLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	fear_ = 0;
	maxFear_ = 100;
	setTexture(fearLevelTexture);
	setPosition(place_, 70);
	setDimension(400, 0);
}

//se asusta y si llega a 100 se desmaya
bool FearLevel::getScared(int amount)
{
	fear_+= amount;
	if (fear_ < 0)fear_ = 0;
	if (fear_ <maxFear_) {
		setDimension(fear_*2, 50);
		setPosition(50 - (amount/2), 70);
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
}

void FearLevel::draw()
{
	drawTexture(texture);
}
