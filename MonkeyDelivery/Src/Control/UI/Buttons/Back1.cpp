#include "Back1.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"


Back1::Back1(int x, int y, int w, int h, Game* game):Button(game,w,h,x,y){
	setTexture(backButtonTexture);
}

void Back1::onCursorCollision(){
	//game->setState(new PlayingState(game));
	ChangeToLastState();
}
