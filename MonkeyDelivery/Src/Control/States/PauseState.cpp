#include "PauseState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"

#include "../UI/Buttons/Options.h"

PauseState::PauseState(Game* game) : State(game)
{
	registerCommands();

	addButton(new Options(game->getWindowWidth() / 2 - 45, game->getWindowHeight()/2, 100, 75, game));

}

void PauseState::update()
{
}

void PauseState::draw()
{

	game->renderText("PAUSED", game->getWindowWidth() / 2 - 65, game->getWindowHeight() / 2 - 150);

	for (auto b : getButtonsUI()) {
		b->draw();
	}
}

void PauseState::next()
{
}

void PauseState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandClick());

	commandFactory->add(new CommandExit());
}
