#include "Continue.h"

#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"

Continue::Continue(int x, int y, int w, int h, Game* game) :Button(game, w, h, x, y)
{
	setTexture(button_Continue);
}

void Continue::onCursorCollision()
{
	//game->setState(new PlayingState(game));
	/*if (game->getSavedState() != nullptr) {
		State* tmp = game->getState();
		State* saved = game->getSavedState();
		saved->resetInitTime();
		saved->registerCommands();
		game->setState(saved);
		game->clearSavedState();
		delete tmp;
	}*/
	ChangeToLastState();
}
