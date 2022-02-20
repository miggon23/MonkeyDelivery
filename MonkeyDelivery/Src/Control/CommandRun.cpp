#include "CommandRun.h"

bool CommandRun::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;

		if (key == SDLK_LSHIFT) {
			isRunning = true;
			return true;
		}
	}

	if (event.type == SDL_KEYUP) {
		SDL_Keycode key = event.key.keysym.sym;

		if (key == SDLK_LSHIFT) {
			isRunning = false;
			return true;
		}
		return false;
	}
	
}

void CommandRun::execute()
{
    game->setIsRunning(isRunning); //Indica si el player corre o no
}
