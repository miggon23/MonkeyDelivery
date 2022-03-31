#include "Rock.h"

Rock::Rock(Game* game, int x, int y) :GameObject(game) {
	setTexture(shopTexture);
	setDimension(x, y);
	setPosition(280.0, 680.0);
}

Rock::~Rock()
{
}
