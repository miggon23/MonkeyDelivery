#include "InteractuableChest.h"
#include "../Logic/Game.h"

InteractuableChest::InteractuableChest(Game* game, int x, int y, int w, int h, int select) : GameObject(game, true), w_(0), h_(0),
																				 rewardT_(nullptr), x_(0), y_(0), timer_(0), selection_(select)
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
		sdlutils().soundEffects().at("chest").setVolume(game->getSoundEfectsVolume()* 2 * game->getGeneralVolume());
		sdlutils().soundEffects().at("chest").play(0, 1);
		
		selectReward(selection_, player);

		active = false;
		timer_ = sdlutils().currRealTime();
		setTexture(worldObject_Chest_Opened);
	}
}

void InteractuableChest::selectReward(int reward, Player* player)
{
	//int randMoney = sdlutils().rand().nextInt(5, 20);
	int randMoney = sdlutils().rand().nextInt(5, 20);
	
	player->decreaseChestCount();
	switch (reward)
	{
	case 0:
		game->newDialogue("Story1");
		rewardT_ = game->getTexture(worldObject_Note);
		break;
	case 1:
		game->newDialogue("Story2");
		rewardT_ = game->getTexture(worldObject_Note);
		break;
	case 2:
		game->newDialogue("Story3");
		rewardT_ = game->getTexture(worldObject_Note);
		break;
	case 3:
		game->newDialogue("Story4");
		rewardT_ = game->getTexture(worldObject_Note);
		break;
	default:
		player->addMoney(randMoney);
		game->newDialogue("ChestMoneyText");
		rewardT_ = game->getTexture(Item_Coins);
		sdlutils().soundEffects().at("moneyBag").setVolume((int)(game->getSoundEfectsVolume() * game->getGeneralVolume()));
		sdlutils().soundEffects().at("moneyBag").play(0, 1);
		break;
	}
}