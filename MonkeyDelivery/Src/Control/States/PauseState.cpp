#include "PauseState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"

PauseState::PauseState(Game* game) : State(game)
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
