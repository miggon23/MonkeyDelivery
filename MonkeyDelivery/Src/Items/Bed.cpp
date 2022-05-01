#include "Bed.h"
#include "../Player/Player.h"

Bed::Bed(Game* game) :GameObject(game, true) {
	setTexture(worldObject_Bed);
	setDimension(93, 138);
}

Bed::Bed(Game* game, int x, int y) : GameObject(game, true)
{
	setPosition(x, y);
	setTexture(worldObject_Bed);
	setDimension(93, 138);
}

Bed::~Bed(){}

void Bed::update(){}

//llamo al metodo para ver si puede dromir
void Bed::onPlayerInteraction(Player* player){
	player->changeSleep();

	if (player->isAsleep())//si te vas a dormir
	{
		player->savePosBeforeSleep();
		player->setPosition((double)getX() + 15, getY());//colocar en la cama
	}
	
}
