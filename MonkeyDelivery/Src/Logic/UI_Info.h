#pragma once

#include "SDL_ttf.h"
#include "../View/Font.h"
#include <string>
#include <vector>

class Game;
class UI_Info
{
private:
	Font* font_;
	Game* game;

public:
	UI_Info(Game* game);
	~UI_Info();

	void drawInfo();

	void draw();

	void renderText(string text, int x, int y, SDL_Color color);
	void renderText(vector<string> text, int x, int y, SDL_Color color);

	void renderImage(string imgRoute);
};
