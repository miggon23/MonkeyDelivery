#include "Credits.h"
#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"
#include "../../States/CreditsState.h"

Credits::Credits(int x, int y, double w, double h, Game* game):Button(game,w,h,x,y){
	setTexture(button_Main_Credits);
}

void Credits::onCursorCollision(){
	
	ChangeToNewState(new CreditsState(game),true);
}
