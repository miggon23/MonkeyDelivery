#include "InteractuableChest.h"
#include "../Logic/Game.h"

InteractuableChest::InteractuableChest(Game* game, int x, int y, int w, int h) : GameObject(game, true), w_(0), h_(0),
																				 rewardT_(nullptr), x_(0), y_(0), timer_(0)
{	
	setTexture(worldObject_Chest_Closed);
	setDimension(w, h);
	setPosition(x, y);
	active = true;
	x_ = game->getWindowWidth() / 2;
	y_ = (game->getWindowHeight() / 2)+100;
	w_ = h_ = 10;
}


void InteractuableChest::draw()
{
	//Si el cofre esta desativado cambiar su textura
	GameObject::draw();
	if (!active && rewardT_ != nullptr && timer_ + limit > sdlutils().currRealTime()) {
		double incr = 0.7;
		rewardT_->render({ (int)(x_ - (w_ / 2)), (int)(y_ - (h_ / 2)),  (int)w_,  (int)h_ });
		if (timer_ + semiLimit > sdlutils().currRealTime()) {
			w_ += incr; h_ += incr;
		}
		else {
			w_ -= incr; h_ -= incr;
		}
	}
}

void InteractuableChest::onPlayerInteraction(Player* player)
{
	if (active) {
		sdlutils().soundEffects().at("chest").setVolume(game->getSoundEfectsVolume()*2);
		sdlutils().soundEffects().at("chest").play(0, 1);

		//0 --> dinero
		//1 --> elementos de la narrativa
		auto rand = sdlutils().rand().nextInt(0, 1);
	
		selectReward(rand, player);

		active = false;
		timer_ = sdlutils().currRealTime();
		setTexture(worldObject_Chest_Opened);
	}
}

void InteractuableChest::selectReward(int reward, Player* player)
{
	//int randMoney = sdlutils().rand().nextInt(5, 20);
	int randMoney = sdlutils().rand().nextInt(5, 20);
	string s = "ChestMoneyText";
	player->addChestCount();
	switch (reward)
	{
	case 0:
		player->addMoney(randMoney);
		game->newDialogue(s);
		rewardT_ = game->getTexture(Item_Coins);
		break;
	case 1:
		//Elementos de la narrativa
		rewardT_ = game->getTexture(UI_Coin);
		break;
	default:
		break;
	}
}