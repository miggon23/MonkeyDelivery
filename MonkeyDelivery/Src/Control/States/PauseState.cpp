#include "PauseState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"

PauseState::PauseState(Game* game, ViewController *v) : State(game,v)
{
	registerCommands();
}

void PauseState::update()
{
}

void PauseState::draw()
{
	game->renderText("PAUSED", game->getWindowWidth() / 2 - 75, game->getWindowHeight() / 2 - 50);
}

void PauseState::next()
{
}

void PauseState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
}
