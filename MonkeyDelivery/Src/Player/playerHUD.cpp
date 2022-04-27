#include "playerHUD.h"
#include "../Logic/Game.h"

playerHUD::playerHUD(Game* game) :GameObject(game) {
	this->game = game;
	setTexture(UI_playerHUD);
	setPosition(20, 20);
	setDimension(game->getWindowWidth()/4.0, game->getWindowHeight()/6.01);
}

void playerHUD::draw()
{
	drawTexture(texture);
}
