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
	
	SDL_Rect rectPanel = { 0,0,game->getWindowWidth(),game->getWindowHeight() };
	panelTexture->render(rectPanel);

	int i = 0;

	//pruebas
	while (i < 2)
	{
		game->getTexture(bullTexture)->render({ xOffset + xObj * i, yOffset, wObj, hObj });
		i++;
	}
	game->getTexture(bullTexture)->render({ xOffset, yOffset + yObj, wObj, hObj });
	//

	//forma render inal
	
	while (i < shop_->getSize())
	{
		shop_->objects[i]->getTexture()->render({ xOffset + xObj * (i-4), yOffset + yObj, wObj, hObj });
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
