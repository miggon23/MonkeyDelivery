#include "OptionsState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../UI/Buttons/Back.h"

OptionsState::OptionsState(Game* game) : State(game)
{
	registerCommands();
	addButton(new Back(game->getWindowWidth() / 2 - 100, game->getWindowHeight() - 250, 100, 75, game, 1));


}

void OptionsState::update()
{
}

void OptionsState::draw()
{
	//game->renderText("PAUSED", game->getWindowWidth() / 2 - 75, game->getWindowHeight() / 2 - 50);
}

void OptionsState::next()
{
}

void OptionsState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
}
