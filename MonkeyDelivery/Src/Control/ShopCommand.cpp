#include "ShopCommand.h"

bool ShopCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		
		if (key == SDLK_SPACE)
		{
			//buy_ = true;
			interaccion_ = -1;
			return true;
		}
		else if (key == SDLK_a) {
			moveCursor_ = -1;
			interaccion_ = 0;
			return true;
		}
		else if (key == SDLK_d) {
			moveCursor_ = 1;
			interaccion_ = 0;
			return true;
		}
		else if (key == SDLK_w) {
			moveCursor_ = -1;	
			interaccion_ = 1;
			return true;
		}
		else if (key == SDLK_s) {
			moveCursor_ = 1;
			interaccion_ = 1;
			return true;
		}
	}
	return false;
}

void ShopCommand::execute()
{
	/*if (buy_)
	{
		shopState_->buySelected();
		buy_ = false;
	}
	else
	{
		shopState_->moveSelectedX(moveCursorX_);
	}*/
	switch (interaccion_)
	{
	case -1:
		shopState_->buySelected();
		
		break;
	case 0:
		shopState_->moveSelectedX(moveCursor_);
		break;
	case 1:
		shopState_->moveSelectedY(moveCursor_);
		break;
	}
}
