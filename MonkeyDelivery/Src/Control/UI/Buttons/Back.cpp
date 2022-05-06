#include "Back.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"


Back::Back(int x, int y, double w, double h, Game* game):Button(game,w,h,x,y){
	setTexture(button_Back);
}

void Back::onCursorCollision(){
	ChangeToLastaStateNO_DELETE_LAST();
}