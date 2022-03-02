#include "SelectMissionCommand.h"
#include "./States/PlayingState.h"
#include "../Logic/MissionsPanel.h"

bool SelectMissionCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_e)
			return true;
	}
	return false;
}

void SelectMissionCommand::execute()
{
	game->getMissionsPanel()->onMissionSelected("Mission01"); // este parámetro depende de qué elemento esté seleccionado
}
