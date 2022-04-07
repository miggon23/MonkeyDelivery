#include "Options.h"
#include "../../../Logic/Game.h"
#include "../../States/OptionsState.h"

Options::Options(int x, int y, int w, int h, Game* game, int num) :Button(game, w, h, x, y){
	setTexture(optionsButtonTexture);
	num_ = num;
}

void Options::onCursorCollision(){	
	//game->setState(new OptionsState(game, num_));	
	//ChangeToNewState(new OptionsState(game, num_),true);
	ChangeToOptionsState();
}