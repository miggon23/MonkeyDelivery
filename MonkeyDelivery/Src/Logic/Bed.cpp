#include "Bed.h"
#include "Player.h"
Bed::Bed(Game* game) :GameObject(game) {
	setTexture(cama);
	setDimension(140, 130);
}

Bed::~Bed()
{
}

void Bed::update()
{	
}
//lllamo al metodo para ver si puede dromir
void Bed::onPlayerInteraction(Player* player){
	player->changeSleep();

	if(player->isAsleep())//si te vas a dormir
	player->setPosition(getX()+15, getY());//colocar en la cama
}
