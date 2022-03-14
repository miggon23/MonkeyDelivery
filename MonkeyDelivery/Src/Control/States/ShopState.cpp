#include "ShopState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"

ShopState::ShopState(Game* game, ViewController *v) : State(game,v){
	registerCommands();
	panelTexture=game->getTexture(shopPanel);
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
	/*for (int i = 0; i < length; i++)
	{

	}*/
	SDL_Rect rectPanel = { xPanel,yPanel,wPanel,hPanel };
	panelTexture->render(rectPanel);
}

void ShopState::next()
{
}

void ShopState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
}
