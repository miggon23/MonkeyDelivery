#include "CommandMoveV.h"

bool CommandMoveV::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;

		if (key == SDLK_w) {
			dir = -1;
			return true;
		}
		else if (key == SDLK_s) {
			dir = 1;
			return true;
		}
	}
	return false;
}

void CommandMoveV::execute()
{
	game->move(pair<double, double>(0, dir));
	dir = 0;
}
