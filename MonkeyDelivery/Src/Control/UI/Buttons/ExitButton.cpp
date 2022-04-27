#include "ExitButton.h"

ExitButton::ExitButton(int x, int y, double w, double h, Game* game):Button(game, w, h, x, y){
	setTexture(button_Main_ExitButton);
}

void ExitButton::onCursorCollision(){
	game->setUserExit();
}