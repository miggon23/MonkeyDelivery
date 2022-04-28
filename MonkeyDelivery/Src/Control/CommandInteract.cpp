#include "CommandInteract.h"
#include "./States/MissionSelectionState.h"
#include "../sdlutils/InputHandler.h"

bool CommandInteract::parse(SDL_Event& event)
{
	auto& ihdlr = ih();
	if ((event.type == SDL_KEYDOWN&& event.key.keysym.sym==SDLK_e) || ihdlr.getButtonState(0, 3)&&(!game->getPlayer()->isMonkeyTalking()))
		return true;
	
	return false;
}

void CommandInteract::execute()
{
	/*if (game->getPlayer()->isMonkeyTalking())
		return;*/

	game->interactDialogue();
	for (GameObject* o : game->getCollisions(game->getPlayer()->getCollider())) {

		//o->exampleInter(game->getPlayer());
		o->onPlayerInteraction(game->getPlayer()); // Podemos poner esto directamente
		return;
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