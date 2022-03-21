#include "PauseState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
<<<<<<< Updated upstream

=======
#include "../UI/Buttons/Options.h"
>>>>>>> Stashed changes

PauseState::PauseState(Game* game) : State(game)
{
	registerCommands();
<<<<<<< Updated upstream
	

=======

	addButton(new Options(game->getWindowWidth() / 2 - 45, game->getWindowHeight()/2, 100, 75, game));
>>>>>>> Stashed changes
}

void PauseState::update()
{
}

void PauseState::draw()
{
<<<<<<< Updated upstream
=======
	game->renderText("PAUSED", game->getWindowWidth() / 2 - 65, game->getWindowHeight() / 2 - 150);
>>>>>>> Stashed changes
	for (auto b : getButtonsUI()) {
		b->draw();
	}
}

void PauseState::next()
{
<<<<<<< Updated upstream
	delete this;
=======
	for (auto b : buttonsUI) {
		delete b;
		b = nullptr;
	}
>>>>>>> Stashed changes
}

void PauseState::registerCommands()
{
<<<<<<< Updated upstream
	//commandFactory->add(new PauseCommand());
=======
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandClick());
>>>>>>> Stashed changes
	commandFactory->add(new CommandExit());
	commandFactory->add(new CommandClick());
}
