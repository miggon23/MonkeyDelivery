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
	SDL_Rect rect = {1550, 10, 170, 180};
	t->render(rect);
	delete t;
}

void UI_Info::drawInfo()
{
	auto* g = game->getMissionsPanel()->getCurrentMission();
	if (g != nullptr) {
		
		// Para mostrar texto en lugar de imagen
		/*renderText(game->getMissionsPanel()->getCurrentMission()->getName(), 700, 15, BLACK);
		if (g->isExpress()) {
			renderText("Time left ", 700, 35, BLACK);
			renderText(to_string(game->getMissionsPanel()->getTime()), 700, 50, BLACK);
		}*/
		renderImage(game->getMissionsPanel()->getMissionImage());
		if (g->isExpress()) {
			renderText("Time left ", 1550, 200, BLACK);
			renderText(to_string(game->getMissionsPanel()->getTime()), 1550, 250, BLACK);
		}
	}
	renderText("Money  " + to_string(game->getPlayer()->money_), 1400, 5, BLACK);
}


void UI_Info::draw()
{
	drawInfo();
}
