#include "CommandRun.h"

bool CommandRun::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;

		if (!isRunning && key == SDLK_LSHIFT) { //Para que la velocidad no se acumule
			isRunning = true;
			return true;
		}
	}

	if (event.type == SDL_KEYUP) {
		SDL_Keycode key = event.key.keysym.sym;

		if (isRunning && key == SDLK_LSHIFT) { 
			isRunning = false;
			return true;
		}
	}
	return false;
}

void CommandRun::execute()
{
	//Mejor que el player no sepa nada del comando, cambiar la velocidad desde aquí mejor
	//  y tener una velocidad inicial del player por si hay que volver a ella
    game->setIsRunning(isRunning); //Indica si el player corre o no
}
