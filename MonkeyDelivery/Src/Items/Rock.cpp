#include "Rock.h"
#include "../Logic/game.h"

Rock::Rock(Game* game, int x, int y,int levelToDestroy) :ColliderTile(game,Vector2D<double>(x,y),w,h) {
	setTexture(worldObject_blockRock);
	levelToDestroy_ = levelToDestroy % 2;
	setDimension(w, h);
	setPosition(x, y);
}

Rock::~Rock(){
}

void Rock::draw(){
	drawTexture(texture);
	drawDebug();
}

