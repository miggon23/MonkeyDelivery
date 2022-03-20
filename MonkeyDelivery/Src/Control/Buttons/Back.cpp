#include "Back.h"
#include "../../Logic/Game.h"
#include "../States/MenuState.h"
#include "../States/PlayingState.h"


Back::Back(int x, int y, int w, int h, Game* game, int num):Button(game,w,h,x,y){
	setTexture(backButtonTexture);
	num_ = num;
}

void Back::onCursorCollision(){
	if(num_ == 1)
	game->setState(new MenuState(game));
	else
	game->setState(new PlayingState(game));

}
