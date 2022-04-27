#include "SelectButtonCommand.h"

SelectButtonCommand::SelectButtonCommand(MenuState* ms) : menuState(ms)
{
}

bool SelectButtonCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_UP) {
			move = -1;
			return true;
		}
		else if (key == SDLK_DOWN) {
			move = 1;
			return true;
		}
		else if (key == SDLK_SPACE || key == SDLK_RETURN) {
			move = 0;
			return true;
		}
	}
	return false;
}

void SelectButtonCommand::execute()
{
	if (move == 0) {
		menuState->getCurrentButton()->onCursorCollision();
	}
	else {
		menuState->moveBox(move);
	}
}
