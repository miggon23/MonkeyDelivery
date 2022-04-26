#include "playerHUD.h"

playerHUD::playerHUD(Game* game) :GameObject(game) {
	this->game = game;
	setTexture(UI_playerHUD);
	setPosition(20, 20);
	setDimension(113*4, 41*4);
}

void playerHUD::draw()
{
	drawTexture(texture);
}
