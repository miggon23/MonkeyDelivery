#include "Credits.h"
#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"

Credits::Credits(int x, int y, int w, int h, Game* game):Button(game,w,h,x,y){
	setTexture(creditsButtonTexture);
}

void Credits::onCursorCollision(){
	game->setState(new PlayingState(game));
}
