#include "InteractuableShop.h"
#include "Player.h"
IntectuableShop::IntectuableShop(Game* game) :GameObject(game) {
	setTexture(cama);
	setDimension(150, 150);
}

IntectuableShop::~IntectuableShop()
{
}

void IntectuableShop::update()
{	
}
//lllamo al metodo para ver si puede dromir
void IntectuableShop::onPlayerInteraction(Player* player){
	//player->changeSleep();
}
