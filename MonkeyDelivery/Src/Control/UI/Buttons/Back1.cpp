#include "Back1.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"


Back1::Back1(int x, int y, double w, double h, Game* game):Button(game,w,h,x,y){
	setTexture(button_Back);
}

void Back1::onCursorCollision(){
	ChangeToLastState();
}