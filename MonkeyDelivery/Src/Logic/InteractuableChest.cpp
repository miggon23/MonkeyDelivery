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
	//active = !active;

	if (active) {
		sdlutils().soundEffects().at("chest").setVolume(game->getSoundEfectsVolume());
		sdlutils().soundEffects().at("chest").play(0, 1);

		//Los numeros variaran en funcion de cuantas recompensas haya
		auto rand = sdlutils().rand().nextInt(0, 1);
	
		selectReward(rand, player);
	}
	active = false;
}

void InteractuableChest::selectReward(int reward, Player* player)
{
	switch (reward)
	{
	case 0:
		rewardT_ = game->getTexture(goldTexture);
		player->addMoney(10);
		break;
	default:
		break;
	}
}