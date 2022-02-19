#pragma once

#include <string>
#include <vector>

class Game;
class UI_Info
{

		Font* font;
		Game* game;


	public:
		UI_Info(Game* game);
		~UI_Info();
		void drawInfo();
		
		void draw(bool help);

		void renderText(string text, float x, float y, SDL_Color color);
		void renderText(vector<string> text, float x, float y, SDL_Color color);

	};
};

