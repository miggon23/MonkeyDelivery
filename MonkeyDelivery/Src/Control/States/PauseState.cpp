#include "PauseState.h"
#include "../PauseCommand.h"

PauseState::PauseState(Game* game) : State(game)
{
	registerCommands();
}

void PauseState::update()
{
	commandFactory->add(new PauseCommand());
}

void PauseState::draw()
{
	game->renderText("PAUSED", game->getWindowWidth() / 2 - 50, game->getWindowHeight() / 2 - 50);
}

void PauseState::next()
{
}

void PauseState::registerCommands()
{
}
