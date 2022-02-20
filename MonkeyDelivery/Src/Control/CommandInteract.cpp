#include "CommandInteract.h"

bool CommandInteract::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_e) {
			return true;
		}
	}
	return false;
}

void CommandInteract::execute()
{
	//game->interactions();

	// adri y simona: lo usamos para la interaccion con los bichos
	
	for (GameObject* o : game->getCollisions(game->getPlayer()->getCollider())) {
		o->exampleInter();
	}
}



