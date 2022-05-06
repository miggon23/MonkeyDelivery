#include "Options.h"
#include "../../../Logic/Game.h"
#include "../../States/OptionsState.h"

Options::Options(int x, int y, double w, double h, Game* game, int num) :Button(game, w, h, x, y){
	setTexture(button_Main_Options);
	num_ = num;
}

void Options::onCursorCollision(){	
	ChangeToOptionsState();
}