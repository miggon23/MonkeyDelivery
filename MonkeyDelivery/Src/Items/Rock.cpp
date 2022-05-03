#include "Rock.h"
#include "../Logic/game.h"

Rock::Rock(Game* game, int x, int y,int levelToDestroy) : ColliderTile(game,Vector2D<double>(x,y), 75.0, 75.0) {
	levelToDestroy_ = levelToDestroy % 2;
	switch (levelToDestroy_){
	case 1:
		setTexture(worldObject_blockRock01);
		break;
	case 2:
		setTexture(worldObject_blockRock02);
		break;
	}
}

Rock::~Rock(){
	isActive_ = false;
	isColliding_ = false;
	onPlayerCollisionExit();
}

void Rock::draw(){
	drawTexture(texture);
}

