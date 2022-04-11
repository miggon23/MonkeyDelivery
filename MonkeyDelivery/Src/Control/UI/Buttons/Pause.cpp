#include "Pause.h"
#include "../../../Logic/Game.h"
#include "../../States/PauseState.h"


Pause::Pause(int x, int y, int w, int h, Game* game):Button(game,w,h,x,y){
	setTexture(button_Pause);
}

void Pause::onCursorCollision(){
    //pause
   /* game->setSaveState(game->getState());
    game->setState(new PauseState(game));*/
    ChangeToNewState(new PauseState(game),true);
}