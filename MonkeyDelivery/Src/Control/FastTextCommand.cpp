#include "FastTextCommand.h"

bool FastTextCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_SPACE) {
			return true;
		}
	}
	return false;
}

void FastTextCommand::execute()
{
	game->fastDialogue();
}
