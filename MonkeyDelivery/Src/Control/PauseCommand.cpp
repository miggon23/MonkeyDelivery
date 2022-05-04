#include "PauseCommand.h"
#include "./States/PauseState.h"
#include "../sdlutils/InputHandler.h"

PauseCommand::PauseCommand(){
}

bool PauseCommand::parse(SDL_Event& event)
{
	auto& ihld = ih();
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_ESCAPE)
			return true;
	}
	else if (ihld.getButtonState(0, 7)) {
  		return true;
	}
	return false;
}

void PauseCommand::execute()
{
	if (game->getInGame() && game->isInitialTransitionComplete()) {
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
