#include "Start.h"
#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"

Start::Start(int x, int y, double w, double h, Game* game):Button(game,w,h,x,y){
	setTexture(button_Main_StartButton);
}

void Start::onCursorCollision(){
	sdlutils().musics().at("menumusic").pauseMusic();
	ChangeToNewState(new PlayingState(game),false);
}