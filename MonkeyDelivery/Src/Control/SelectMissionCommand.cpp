#include "SelectMissionCommand.h"
#include "./States/PlayingState.h"
#include "../Logic/MissionsPanel.h"

bool SelectMissionCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_e) {
			moveCursor_ = 0;
			return true;
		}
		else if (key == SDLK_a) {
			moveCursor_ = -1;
			return true;
		}
		else if (key == SDLK_d) {
			moveCursor_ = 1;
			return true;
		}
	}
	return false;
}

void SelectMissionCommand::execute()
{
	if (moveCursor_ == 0) {
		game->getMissionsPanel()->onMissionSelected(missionSelection_->getSelectedMission()); // este parámetro depende de qué elemento esté seleccionado
	}
	else {
		missionSelection_->moveBox(moveCursor_);
	}
}