#include "UI_Info.h"
#include <iostream>
#include "../Logic/Game.h"

UI_Info::UI_Info(Game* game)
{
	this->game = game;
	font_ = new Font("../Images/TheMoon.ttf", 50);
	
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

void UI_Info::renderImage(string imgRoute)
{
	Texture* t = new Texture(game->getRenderer(), imgRoute);
	SDL_Rect rect = {1300, 10, 24 * 4, 24 * 4};
	t->render(rect);
	delete t;
}

void UI_Info::drawInfo()
{
	auto* g = game->getMissionsPanel()->getCurrentMission();
	if (g != nullptr) 
	{
		renderImage(game->getMissionsPanel()->getMissionImage());
		if (g->isExpress()) {
			renderText(to_string(game->getMissionsPanel()->getTime()), 1300, 70, BLACK);
		}
	}
	//renderText("Money  " + to_string(game->getPlayer()->money_), 1300, 20, BLACK);
}

void UI_Info::draw()
{
	drawInfo();
}
