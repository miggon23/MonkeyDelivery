#include "MapCommand.h"
#include "../Control/States/MapState.h"
#include "../Control/States/State.h"


MapCommand::MapCommand() {}

bool MapCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_m)
			return true;
	}
	return false;
}

void MapCommand::execute()
{
	if (!game->getOpenedMap()) {
		game->setSaveState(game->getState());
		game->setState(new MapState(game));
		game->setOpenedMap(true);
	}
		
	else {
		game->setOpenedMap(false);
		State* tmp = game->getState();
		State* saved = game->getSavedState();
		saved->resetInitTime();
		saved->registerCommands();
		game->setState(saved);
		game->scalePoint();
		game->removeSavedState();
		delete tmp;
	}
}