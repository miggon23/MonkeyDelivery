#include "PauseState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"


PauseState::PauseState(Game* game) : State(game)
{
	registerCommands();
	

}

void PauseState::update()
{
}

void PauseState::draw()
{
	for (auto b : getButtonsUI()) {
		b->draw();
	}
}

void PauseState::next()
{
	delete this;
}

void PauseState::registerCommands()
{
	//commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
	commandFactory->add(new CommandClick());
}
