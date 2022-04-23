#include "InventoryCommand.h"
#include "../sdlutils/InputHandler.h"
bool InventoryCommand::parse(SDL_Event& event) {
	auto& ihdlr = ih();

	if (event.type == SDL_MOUSEWHEEL) {
		ruedaRton = true;
		id = event.wheel.y;
		//std::cout << id << std::endl;
		return true;
	}

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
		if (id != -1 || use)
			return true;
	}
	if (ihdlr.bJoysticksInitialised()) {
		use = false;
		//id = -1;
		if (ihdlr.getButtonState(0, 5)) {
			id++;
			if (id > 5) id = 0;
		}
		if (ihdlr.getButtonState(0, 4)) {
			if (id != -1)
				id--;
			if (id == 0) id = 5;
		}
		if (ihdlr.getButtonState(0, 0))use = true;
		//cout << id;
		if (id != -1 || use)
			return true;

	}
	return false;
}

void InventoryCommand::execute() {
	if (use) { game->getPlayer()->useSelectedObject(); use = false; return; }
	else if (ruedaRton) { 
		//std::cout << "entra" << std::endl;
		game->getPlayer()->mouseWheelSelectedObject(-id); ruedaRton = false; return; }
	game->getPlayer()->selectObject(id);
	
	//game->useInventory(id);
}
