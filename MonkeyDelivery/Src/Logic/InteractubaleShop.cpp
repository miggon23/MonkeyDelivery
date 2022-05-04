#include "InteractuableShop.h"
#include "../Player/Player.h"
#include "../Control/States/ShopState.h"

IntectuableShop::IntectuableShop(Game* game,int x , int y) : GameObject(game, true) {
	setTexture(ShopPanel_Interact);
	setPosition(x, y);
	setDimension(108, 160);

	width_ = 34;
	height_ = 48;
	time_ = 300;
	maxX_ = 35;
	maxY_ = 0;
	textureRect = { 0, 0, width_, height_ };
	timerAnimation_ = 0; // ¿puede ser const?
}

IntectuableShop::~IntectuableShop() {}

void IntectuableShop::update() {}

void IntectuableShop::draw()
{
	auto pos = getCollider();
	pos.x -= (int)game->getCamera()->getCameraPosition().getX();
	pos.y -= (int)game->getCamera()->getCameraPosition().getY();

	animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
}

//llamo al metodo para ver si puede dromir
void IntectuableShop::onPlayerInteraction(Player* player){	
	game->setSaveState(game->getState());
	game->setState(new ShopState(game));
	game->InGame();
}