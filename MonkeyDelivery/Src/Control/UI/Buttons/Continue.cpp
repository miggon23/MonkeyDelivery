#include "Continue.h"

#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"

Continue::Continue(int x, int y, double w, double h, Game* game) :Button(game, w, h, x, y)
{
	setTexture(button_Continue);
}

void Continue::onCursorCollision()
{
	ChangeToLastState();
}
