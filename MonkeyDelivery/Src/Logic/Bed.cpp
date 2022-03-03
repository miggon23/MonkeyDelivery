#include "Bed.h"
#include "Player.h"
Bed::Bed(Game* game) :GameObject(game) {
	setTexture(cama);
	setDimension(150, 150);
}

Bed::~Bed()
{
}

void Bed::update()
{	
}

void Bed::onPlayerInteraction(Player* player){
	player->changeSleep();
}
