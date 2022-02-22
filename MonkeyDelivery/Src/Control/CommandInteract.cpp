#include "CommandInteract.h"
#include "./States/MissionSelectionState.h"

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
	game->interactions();

	// adri y simona: lo usamos para la interaccion con los bichos
	
	for (GameObject* o : game->getCollisions(game->getPlayer()->getCollider())) {

		if (o->isMissionPanel()) {

			if (game->getSavedState() == nullptr) {
				// show pannel
				game->saveState(game->getState());
				game->setState(new MissionSelectionState(game));
			}
			else {
				game->setActiveMission(new Mission(game->getMissionManager(), game->getiE(), 100, 100, 10, 1000, "Misión 1"));

				// hide pannel
				State* tmp = game->getState();
				State* saved = game->getSavedState();
				saved->resetInitTime();
				saved->registerCommands();
				game->setState(saved);
				game->clearSavedState();
				delete tmp;
			}
		}
		else {
			o->exampleInter();
		}
	}
}



