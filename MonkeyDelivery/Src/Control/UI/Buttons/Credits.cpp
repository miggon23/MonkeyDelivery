#include "Credits.h"
#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"
#include "../../States/CreditsState.h"

Credits::Credits(int x, int y, double w, double h, Game* game):Button(game,w,h,x,y){
	setTexture(button_Main_Credits);
}

void Credits::onCursorCollision(){
	//game->setState(new CreditsState(game));
	/*sdlutils().musics().at("menumusic").pauseMusic();
	sdlutils().musics().at("creditsmusic").play(-1);*/	
	ChangeToNewState(new CreditsState(game),true);
}
