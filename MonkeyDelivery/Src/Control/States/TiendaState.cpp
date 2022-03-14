#include " ShopState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"

ShopState::ShopState(Game* game, ViewController *v) : State(game,v)
{
	registerCommands();
}

void ShopState::update()
{
}

void ShopState::draw()
{
	game->renderText("PAUSED", game->getWindowWidth() / 2 - 75, game->getWindowHeight() / 2 - 50);
}

void ShopState::next()
{
}

void ShopState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
}
