#include "PauseCommand.h"
#include "./States/PauseState.h"


PauseCommand::PauseCommand(){
}

bool PauseCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_ESCAPE)
			return true;
	}
	return false;
}

void PauseCommand::execute()
{
	if (game->getInGame()) {
		//pause
		game->setSaveState(game->getState());
		game->setState(new PauseState(game));
		game->InGame();
	}
	else {
		// unpause
		game->InGame();
		if (game->saveStateEmpty())return;//por si no hay ningun estado

		State* tmp = game->getState();
		game->ClearState();
		State* saved = game->getSavedState();
		//saved->resetInitTime();
		game->setState(saved);
		game->removeSavedState();
		delete tmp;
	}
}
