#include "Rock.h"
#include "../Logic/game.h"
Rock::Rock(Game* game, int x, int y) :GameObject(game, true) {
	setTexture(rocaTexture);
	setDimension(100.0, 100.0);
	setPosition(x, y);
}

Rock::~Rock(){
}

void Rock::update(){
}

void Rock::onPlayerInteraction(Player* player){
	if (player->getActiveItemObject()=="Pickaxe") {
		// quitarle un uso al pico
		game->removeGameObject(this);
	}
}
