#include "playerHUD.h"
#include "../Logic/Game.h"

playerHUD::playerHUD(Game* game) :GameObject(game),baseRect_()
{
	this->game = game;
	HUD_Base = game->getTexture(UI_playerHUD);
	HUD_Fill = game->getTexture(UI_playerHUD_BackFill);
	setPosition(20, 20);
	//setDimension(game->getWindowWidth() / 4.0, game->getWindowHeight() / 6.01);

	x = (int)(game->getWindowWidth() / 90.0);
	y = (int)(game->getWindowHeight() / 50.0);
	w = (int)(game->getWindowWidth() / 3.982);
	h = (int)(game->getWindowHeight() / 6.098);
}

void playerHUD::drawFillHUD()
{
	baseRect_ = { x, y , w, h };
	HUD_Fill->render(baseRect_);
}void playerHUD::drawOverHUD()
{
	baseRect_ = { x, y , w, h };
	HUD_Base->render(baseRect_);
}