#include "Options.h"
#include "../../Logic/Game.h"
#include "../States/OptionsState.h"
Options::Options(int x, int y, int w, int h, Game* game, ViewController* v) :Button(game, w, h, x, y,v){
}

void Options::onCursorCollision(){
	game->setState(new OptionsState(game,v_));
}