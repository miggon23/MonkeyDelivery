#include "InventoryCommand.h"

bool InventoryCommand::parse(SDL_Event & event) {

	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;

		id = -1;
		if (key == SDLK_0) id = 0;
		if (key == SDLK_1) id = 1;
		if (key == SDLK_2) id = 2;
		if (key == SDLK_3) id = 3;
		if (key == SDLK_4) id = 4;
		if (key == SDLK_5) id = 5;
		if (id != -1)
			return true;
	}
	return false;
}

void InventoryCommand::execute() {
	game->useInventory(id);
}
