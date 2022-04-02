#include "InteractuableChest.h"
#include "../Logic/Game.h"

InteractuableChest::InteractuableChest(Game* game, int x, int y, int w, int h) : GameObject(game)
{	
	setTexture(chestTexture);
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
		sdlutils().soundEffects().at("chest").setVolume(game->getSoundEfectsVolume());
		sdlutils().soundEffects().at("chest").play(0, 1);

		//0 --> dinero
		//1 --> elementos de la narrativa
		auto rand = sdlutils().rand().nextInt(0, 1);
	
		selectReward(rand, player);

		active = false;

		setTexture(openChestTexture);
	}
}

void InteractuableChest::selectReward(int reward, Player* player)
{
	int randMoney = sdlutils().rand().nextInt(5, 20);
	switch (reward)
	{
	case 0:
		rewardT_ = game->getTexture(goldTexture);
		player->addMoney(randMoney);
		break;
	case 1:
		//Elementos de la narrativa
		break;
	default:
		break;
	}
}