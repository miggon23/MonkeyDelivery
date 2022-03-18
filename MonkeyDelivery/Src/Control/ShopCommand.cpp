#include "ShopCommand.h"

bool ShopCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		
		if (key == SDLK_LEFT) {
			moveCursor_ = -1;
			return true;
		}
		else if (key == SDLK_RIGHT) {
			moveCursor_ = 1;
			return true;
		}
	}
	return false;
}

void ShopCommand::execute()
{
	shopState_->moveSelected(moveCursor_);
}
