#include "InteractuableShop.h"
#include "Player.h"
#include "../Control/States/ShopState.h"
IntectuableShop::IntectuableShop(Game* game,int x , int y) :GameObject(game) {
	setTexture(shopTexture);
	setDimension(x, y);
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
	game->saveState(game->getState());
	game->setState(new ShopState(game));
}
