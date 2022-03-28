#include "Back.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"


Back::Back(int x, int y, int w, int h, Game* game):Button(game,w,h,x,y){
	setTexture(backButtonTexture);
}

void Back::onCursorCollision(){
	//game->setState(new MenuState(game));
	ChangeToLastState();
}
