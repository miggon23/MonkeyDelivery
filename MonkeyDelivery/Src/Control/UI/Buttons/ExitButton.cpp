#include "ExitButton.h"

ExitButton::ExitButton(int x, int y, int w, int h, Game* game):Button(game, w, h, x, y){
	setTexture(pauseButtonTexture);
}

void ExitButton::onCursorCollision(){
	game->setUserExit();
}
