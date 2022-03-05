#include "UI_Info.h"
#include <iostream>
#include "../Logic/Game.h"

UI_Info::UI_Info(Game* game)
{
	this->game = game;
	font_ = new Font("../Images/TheMoon.ttf", 20);
	
}
UI_Info::~UI_Info()	
{
	game = nullptr;
	delete font_;
	font_ = nullptr;
}

void UI_Info::renderText(string text, int x, int y, SDL_Color color)
{
	font_->render(game->getRenderer(), text.c_str(), x, y, color);
}

void UI_Info::renderText(vector<string> text, int x, int y, SDL_Color color)
{
	for (int i = 0; i < text.size(); i++)
	{
		font_->render(game->getRenderer(), text[i].c_str(), x, y + i * 10, color);
	}

}

void UI_Info::drawInfo()
{
	if (game->getMissionsPanel()->getCurrentMission() != nullptr) {

		renderText(game->getMissionsPanel()->getCurrentMission()->getName(), 700, 15, BLACK);
	}
	//renderText(game->getMissionManager()->getMissionName(), 700, 15, BLACK);
	renderText(to_string(game->getPlayer()->money_), 700, 45, BLACK);
}


void UI_Info::draw()
{
	drawInfo();
}
