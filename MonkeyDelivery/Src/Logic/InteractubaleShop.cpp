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

	itemsTex_= game->getTexture(shop_Items);
	sellerTex_ = game->getTexture(npc_Seller);
}

IntectuableShop::~IntectuableShop() { itemsTex_ = nullptr; sellerTex_ = nullptr; }

void IntectuableShop::update() {}

void IntectuableShop::draw()
{
	auto pos = getCollider();
	pos.x -= (int)game->getCamera()->getCameraPosition().getX();
	pos.y -= (int)game->getCamera()->getCameraPosition().getY();

	SDL_Rect rect = { pos.x,pos.y+100,60,60 };
	SDL_Rect dest = {0,0,20,20};

	animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
	animationManager->getFrameImage(rect, dest, sellerTex_, timerAnimation_, SDL_FLIP_NONE, 20, 20, 40, 0, time_);

	itemsTex_->render({ pos.x-60, pos.y+30, 210, 40 });
}

//llamo al metodo para ver si puede dromir
void IntectuableShop::onPlayerInteraction(Player* player){	
	game->setSaveState(game->getState());
	game->setState(new ShopState(game));
	game->InGame();
}