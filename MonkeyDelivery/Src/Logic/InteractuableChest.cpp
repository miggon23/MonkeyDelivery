#include "InteractuableChest.h"
#include "../Logic/Game.h"

InteractuableChest::InteractuableChest(Game* game, int x, int y, int w, int h, int reward) : GameObject(game)
{	
	setTexture(chestTexture);
	setDimension(w, h);
	setPosition(x, y);
	selectReward(reward);
}



void InteractuableChest::draw()
{
	GameObject::draw();
	if (active && rewardT_ != nullptr)
		rewardT_->render({x, y, w, h});
}

void InteractuableChest::onPlayerInteraction(Player* player)
{
	active = !active;

	sdlutils().soundEffects().at("chest").setVolume(game->getSoundEfectsVolume());
	sdlutils().soundEffects().at("chest").play(0, 1);
	

}

void InteractuableChest::selectReward(int reward)
{
	switch (reward)
	{
	case 0:
		rewardT_ = game->getTexture(goldTexture);
		break;
	default:
		break;
	}
}
