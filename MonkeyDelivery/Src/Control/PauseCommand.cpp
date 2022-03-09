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
		game->saveState(game->getState());
		game->setState(new PauseState(game, nullptr));
	}
	else {
		// unpause
		State* tmp = game->getState();
		State* saved = game->getSavedState();
		saved->resetInitTime();
		saved->registerCommands();
		game->setState(saved);
		game->clearSavedState();
		delete tmp;
	}
}
