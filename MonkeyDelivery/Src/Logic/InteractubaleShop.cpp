#include "InteractuableShop.h"
#include "../Player/Player.h"
#include "../Control/States/ShopState.h"

IntectuableShop::IntectuableShop(Game* game,int x , int y) :GameObject(game, true) {
	setTexture(ShopPanel_Interact);
	setPosition(3350, 1450);
	setDimension(108, 160);
}

IntectuableShop::~IntectuableShop() {}

void IntectuableShop::update() {}

//llamo al metodo para ver si puede dromir
void IntectuableShop::onPlayerInteraction(Player* player){	
	game->setSaveState(game->getState());
	game->setState(new ShopState(game));
	game->InGame();
}