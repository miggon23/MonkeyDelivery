#include "SelectButtonCommand.h"
#include "../sdlutils/InputHandler.h"

SelectButtonCommand::SelectButtonCommand(State* ms) : state(ms)
{
	move = { 0, 0 };
}

bool SelectButtonCommand::parse(SDL_Event& event)
{
	auto& ihdlr = ih();

	if (ihdlr.yvalue(0, 0) == -1  || ihdlr.isKeyDown(SDL_SCANCODE_UP)) {
		move = { 0, -1 };
		return true;
	}
	else if (ihdlr.yvalue(0, 0) == 1 || ihdlr.isKeyDown(SDL_SCANCODE_DOWN)) {
		move = { 0, 1 };
		return true;
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_RIGHT) || ihdlr.xvalue(0, 0) == 1) {
		move = { 1, 0 };
		return true;
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT) || ihdlr.xvalue(0, 0) == -1) {
		move = { -1, 0 };
		return true;
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE) || ihdlr.isKeyDown(SDL_SCANCODE_RETURN) || ihdlr.getButtonState(0, 0)) {
		move = { 0, 0 };
		return true;
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
