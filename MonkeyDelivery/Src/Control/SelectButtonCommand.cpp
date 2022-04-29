#include "SelectButtonCommand.h"

SelectButtonCommand::SelectButtonCommand(State* ms) : state(ms)
{
	move = { 0, 0 };
}

bool SelectButtonCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_UP) {
			move = { 0, -1 };
			return true;
		}
		else if (key == SDLK_DOWN) {
			move = { 0, 1 };
			return true;
		}
		else if (key == SDLK_RIGHT) {
			move = { 1, 0 };
			return true;
		}
		else if (key == SDLK_LEFT) {
			move = { -1, 0 };
			return true;
		}
		else if (key == SDLK_SPACE || key == SDLK_RETURN) {
			move = { 0, 0 };
			return true;
		}
	}
	return false;
}

void SelectButtonCommand::execute()
{
	if (move.getX() == 0 && move.getY() == 0) {
		if (state->getCurrentButton() != nullptr)
			state->getCurrentButton()->onCursorCollision();
	}
	else {
		state->moveBox(move);
	}
}
