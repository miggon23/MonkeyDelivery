#include "CommandInteract.h"
#include "./States/MissionSelectionState.h"
#include "../sdlutils/InputHandler.h"

bool CommandInteract::parse(SDL_Event& event)
{
	auto& ihdlr = ih();
	if ((event.type == SDL_KEYDOWN&& event.key.keysym.sym==SDLK_e) || ihdlr.getButtonState(0, 3)&&(!game->getPlayer()->isTalking()))
		return true;
	
	return false;
}

void CommandInteract::execute()
{
	if (game->interactDialogue()) {
		return;
	}

	for (GameObject* o : game->getCollisions(game->getPlayer()->getCollider())) {

		o->onPlayerInteraction(game->getPlayer());
		return;
	}
}