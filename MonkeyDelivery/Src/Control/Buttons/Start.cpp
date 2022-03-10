#include "Start.h"
#include "../../Logic/Game.h"
#include "../States/PlayingState.h"
Start::Start(int x, int y, int w, int h, Game* game, ViewController* v):Button(game,w,h,x,y,v){
	//setTexture();
}

void Start::onCursorCollision(){
	game->setState(new PlayingState(game,v_));
}
