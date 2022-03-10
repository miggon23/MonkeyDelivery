#include "Exit.h"
#include "../../Logic/Game.h"
Exit::Exit(int x, int y, int w, int h, Game* game, ViewController* v) :Button(game, w, h, x, y,v)
{
}

void Exit::onCursorCollision(){
	game->setUserExit();
}
