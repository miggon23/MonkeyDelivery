#include "CommandMove.h"

bool CommandMove::parse(SDL_Event& event)
{
	
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;

		if (key == SDLK_d) {
			dir = 1;
			return true;
		}
		else if (key == SDLK_a) {
			dir = -1;
			return true;
		}
	}
	return false;
}

void CommandMove::execute()
{
	game->move(pair<double, double>(dir, 0));
	dir = 0;
}
