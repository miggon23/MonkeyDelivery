#include "InventoryCommand.h"

bool InventoryCommand::parse(SDL_Event & event) {

	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		use = false;
		id = -1;
		if (key == SDLK_1) id = 0;
		if (key == SDLK_2) id = 1;
		if (key == SDLK_3) id = 2;
		if (key == SDLK_4) id = 3;
		if (key == SDLK_5) id = 4;
		if (key == SDLK_6) id = 5;
		if (key == SDLK_SPACE)use = true;
			
		if(id!=-1||use)
			return true;
	}
	return false;
}

void InventoryCommand::execute() {
	if (use) { game->getPlayer()->useSelectedObject(); return; }
	game->getPlayer()->selectObject(id);
	//game->useInventory(id);
}
