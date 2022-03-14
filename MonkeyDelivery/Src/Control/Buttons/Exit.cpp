#include "Exit.h"
#include "../../Logic/Game.h"
Exit::Exit(int x, int y, int w, int h, Game* game) :Button(game, w, h, x, y)
{
}

void Exit::onCursorCollision(){
	game->setUserExit();
}
