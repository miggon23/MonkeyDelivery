#include "Rock.h"
#include "../Logic/game.h"

Rock::Rock(Game* game, int x, int y) :ColliderTile(game,Vector2D<double>(x,y),w,h) {
	setTexture(rocaTexture);
	setDimension(w, h);
	setPosition(x, y);
}

Rock::~Rock(){
}

void Rock::draw(){
	drawTexture(texture);
	drawDebug();
}

