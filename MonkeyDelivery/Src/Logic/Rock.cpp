#include "Rock.h"

Rock::Rock(Game* game, int x, int y) :GameObject(game) {
	setTexture(rocaTexture);
	setDimension(100.0, 100.0);
	setPosition(x, y);
}

Rock::~Rock(){
}

void Rock::update(){


}
