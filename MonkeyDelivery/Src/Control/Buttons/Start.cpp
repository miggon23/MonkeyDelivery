#include "Start.h"
#include "../../Logic/Game.h"
#include "../States/PlayingState.h"
Start::Start(int x, int y, int w, int h, Game* game):Button(game,w,h,x,y){
}

void Start::onCursorCollision(){
	game->setState(new PlayingState(game));
}
