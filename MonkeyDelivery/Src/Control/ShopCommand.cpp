#include "ShopCommand.h"

bool ShopCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		
		if (key == SDLK_SPACE)
		{
			buy_ = true;
			return true;
		}
		else if (key == SDLK_LEFT) {
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
	if (buy_)
	{
		shopState_->buySelected();
		buy_ = false;
	}
	else
	{
		shopState_->moveSelected(moveCursor_);
	}

}
