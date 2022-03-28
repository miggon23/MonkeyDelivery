#include "MapCommand.h"

MapCommand::MapCommand()
{
}

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
	if (!open) 
		open = true;
	
	else 
		open = false;
	
	game->setOpenedMap(open);
}
