#include "ExitButton.h"

ExitButton::ExitButton(int x, int y, int w, int h, Game* game):Button(game, w, h, x, y){
	setTexture(exitButtonTexture);
}

void ExitButton::onCursorCollision(){
	game->setUserExit();
}
