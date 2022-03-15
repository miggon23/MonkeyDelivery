#include "ShopState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../../Logic/Shop.h"

ShopState::ShopState(Game* game) : State(game){
	registerCommands();
	panelTexture=game->getTexture(shopPanel);
	shop_ = game->getShop();
	shop_->actualice();
}

ShopState::~ShopState()
{
	//delete panelTexture;
	panelTexture = nullptr;
}


void ShopState::update()
{
}

void ShopState::draw()
{
	//game->renderText("PAUSED", game->getWindowWidth() / 2 - 75, game->getWindowHeight() / 2 - 50);
	
	SDL_Rect rectPanel = { xPanel,yPanel,wPanel,hPanel };
	panelTexture->render(rectPanel);

	int i = 0;
	while (i < shop_->getSize() && i < 4)
	{
		shop_->objects[i]->getTexture()->render({ xObj * i, yObj, wObj, hObj });
		i++;
	}

	while (i < shop_->getSize())
	{
		shop_->objects[i]->getTexture()->render({ xObj * (i-4), yObj * 2, wObj, hObj });
		i++;
	}
	

}

void ShopState::next()
{
}

void ShopState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
}
