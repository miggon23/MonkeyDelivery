#include "FearLevel.h"
#include "..\Logic\Game.h"

FearLevel::FearLevel(Game* game) :GameObject(game), w(0) {
	this->game = game;

	place_ = 50;
	fear_ = 0;
	maxFear_ = 100;
	setTexture(UI_fearLevel);

	x = (int)(game->getWindowWidth() / 7.5);
	y = (int)(game->getWindowHeight() / 23);
	h = (int)(game->getWindowHeight() / 60);

	scale_ = (1.76 / 1800) * game->getWindowWidth();

	setPosition(x, y);
	setDimension(100 * scale_, h);

}

//se asusta y si llega a 100 se desmaya
bool FearLevel::getScared(double amount)
{
	fear_+= amount;
	if (fear_ < 0) fear_ = 0;
	else if (fear_ > maxFear_) fear_ = maxFear_;
	if (fear_ < maxFear_) {
		setDimension(fear_*scale_, h);
		setPosition(x - (amount/2), y);
		draw();
		return false;
	}
	else return true;
}

void FearLevel::resetFear()
{
	fear_ = 0;
	getScared(fear_);
}

void FearLevel::draw()
{
	setDimension(fear_ * 1.68, h);
	setPosition(x , y);
	drawTexture(texture);
}