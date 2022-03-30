#include "InteractuableShop.h"
#include "Player.h"
#include "../Control/States/ShopState.h"
IntectuableShop::IntectuableShop(Game* game,int x , int y) :GameObject(game, true) {
	setTexture(shopTexture);
	setDimension(x, y);
	setPosition(280.0, 680.0);
}

IntectuableShop::~IntectuableShop()
{
}

void IntectuableShop::update()
{	
}
//llamo al metodo para ver si puede dromir
void IntectuableShop::onPlayerInteraction(Player* player){
	//player->changeSleep();
	game->saveState(game->getState());
	game->setState(new ShopState(game));
}
