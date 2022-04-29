#include "UI_Info.h"
#include <iostream>
#include "../Logic/Game.h"

UI_Info::UI_Info(Game* game)
{
	this->game = game;
	font_ = new Font("./Images/fonts/Pixellari.ttf", 20);

	xP = textX = game->getWindowWidth() / 1.36;
	textY = game->getWindowHeight() / 13.28;
	yP = game->getWindowHeight() / 100.0;
	//wP = game->getWindowWidth() / 4.14;//si pones esto así no consigues que escale, solo se estira
	//hP = game->getWindowWidth() / 13.0;//si pones esto así no consigues que escale, solo se estira
	
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
	SDL_Rect rect = {xP, yP, 435, 77}; //ancho largo es fijo para todos los helpers
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
			SDL_Color darkBlue = { 7, 24, 32, 0};
			renderText(to_string(game->getMissionsPanel()->getTime()/10), textX, textY, darkBlue);
		}
	}
	
	//renderText("Money  " + to_string(game->getPlayer()->money_), 1300, 20, BLACK);
}


void UI_Info::draw()
{
	drawInfo();
}
