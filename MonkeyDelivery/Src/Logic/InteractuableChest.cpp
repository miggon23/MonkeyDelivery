#include "InteractuableChest.h"
#include "../Logic/Game.h"

InteractuableChest::InteractuableChest(Game* game, int x, int y, int w, int h) : GameObject(game, true), rewardT_(nullptr)
{	
	setTexture(worldObject_Chest_Closed);
	setDimension(w, h);
	setPosition(x, y);
	active = true;
}


void InteractuableChest::draw()
{
	//Si el cofre esta desativado cambiar su textura
	GameObject::draw();
	if (active && rewardT_ != nullptr)
		rewardT_->render({x, y, w, h});
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

		setTexture(worldObject_Chest_Opened);
	}
}

void InteractuableChest::selectReward(int reward, Player* player)
{
	//int randMoney = sdlutils().rand().nextInt(5, 20);
	int randMoney = sdlutils().rand().nextInt(5, 20);
	string s = "ChestMoneyText";
	switch (reward)
	{
	case 0:
		player->addMoney(randMoney);
		game->newDialogue(s);
		break;
	case 1:
		//Elementos de la narrativa
		rewardT_ = game->getTexture(UI_Coin);
		break;
	default:
		break;
	}
}