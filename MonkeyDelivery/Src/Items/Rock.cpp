#include "Rock.h"
#include "../Logic/game.h"

Rock::Rock(Game* game, int x, int y,int levelToDestroy) :ColliderTile(game,Vector2D<double>(x,y),w,h) {
	levelToDestroy_ = levelToDestroy % 2;
	switch (levelToDestroy_){
	case 1:
		setTexture(worldObject_blockRock01);
		break;
	case 2:
		setTexture(worldObject_blockRock02);
		break;
	}
	setDimension(w, h);
	setPosition(x, y);
}

Rock::~Rock(){
}

void Rock::draw(){
	drawTexture(texture);
	drawDebug();
}

