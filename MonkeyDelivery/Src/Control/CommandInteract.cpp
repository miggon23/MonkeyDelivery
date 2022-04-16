#include "CommandInteract.h"
#include "./States/MissionSelectionState.h"
#include "../sdlutils/InputHandler.h"

bool CommandInteract::parse(SDL_Event& event)
{
	auto& ihdlr = ih();
	if (ihdlr.isKeyDown(SDL_SCANCODE_E) || ihdlr.getButtonState(0, 3))
		return true;
	
	return false;
}

void CommandInteract::execute()
{
	for (GameObject* o : game->getCollisions(game->getPlayer()->getCollider())) {

		//o->exampleInter(game->getPlayer());
		o->onPlayerInteraction(game->getPlayer()); // Podemos poner esto directamente

		// esto era para la forma "cutre" del panel de misiones
		//if (o->isMissionPanel()) {

		//	if (game->getSavedState() == nullptr) {
		//		// show pannel
		//		game->saveState(game->getState());
		//		game->setState(new MissionSelectionState(game));
		//	}
		//	else {
		//		game->setActiveMission(new Mission(game->getMissionManager(), game->getiE(), 100, 100, 10, 1000, "Misión 1"));

		//		// hide pannel
		//		State* tmp = game->getState();
		//		State* saved = game->getSavedState();
		//		saved->resetInitTime();
		//		saved->registerCommands();
		//		game->setState(saved);
		//		game->clearSavedState();
		//		delete tmp;
		//	}
		//}
		//else {
		//	
		//}
	}
}