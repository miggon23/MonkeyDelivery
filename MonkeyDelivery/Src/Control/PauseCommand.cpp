#include "PauseCommand.h"
#include "./States/PauseState.h"


PauseCommand::PauseCommand()
{
}

bool PauseCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_p)
			return true;
	}
	return false;
}

void PauseCommand::execute()
{
	if (game->getSavedState() == nullptr) {
		//pause
		game->setSaveState(game->getState());
		game->setState(new PauseState(game));
	}
	else {
		// unpause
		if (game->saveStateEmpty())return;//por si no hay ningun estado

		State* tmp = game->getState();
		State* saved = game->getSavedState();
		saved->resetInitTime();
		saved->registerCommands();
		game->setState(saved);
		game->removeSavedState();
		delete tmp;
	}
}
