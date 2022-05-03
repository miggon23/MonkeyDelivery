#include "playerHUD.h"
#include "../Logic/Game.h"

playerHUD::playerHUD(Game* game) :GameObject(game) 
{
	this->game = game;
	HUD_Base = game->getTexture(UI_playerHUD);
	HUD_Fill = game->getTexture(UI_playerHUD_BackFill);
	setPosition(20, 20);
	//setDimension(game->getWindowWidth() / 4.0, game->getWindowHeight() / 6.01);
}

void playerHUD::drawFillHUD()
{
	baseRect_ = { 20, 20 , 113 * 4, 41 * 4 };
	HUD_Fill->render(baseRect_);
}void playerHUD::drawOverHUD()
{
	baseRect_ = { 20, 20 , 113 * 4, 41 * 4 };
	HUD_Base->render(baseRect_);
}