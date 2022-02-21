#include "CommandMove.h"

bool CommandMove::parse(SDL_Event& event)
{

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A]) {
		dir = -1;
		game->move(pair<double, double>(dir, 0));
	}
	else if (state[SDL_SCANCODE_D]) {
		dir = 1;
		game->move(pair<double, double>(dir, 0));
	}
	else dir = 0;
	if (state[SDL_SCANCODE_S]) {
		dirV = 1;
		game->move(pair<double, double>(0, dirV));
	}
	else if (state[SDL_SCANCODE_W]) {
		dirV = -1;
		game->move(pair<double, double>(0, dirV));
	}
	else dirV = 0;
	return false;
}

void CommandMove::execute()
{
	game->move(pair<double, double>(dir, dirV)); //Movimiento del player
	
}
