#include "OptionsState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../UI/Buttons/Back.h"

OptionsState::OptionsState(Game* game) : State(game)
{
	registerCommands();
	addButton(new Back(game->getWindowWidth() / 2 - 100, game->getWindowHeight() - 250, 100, 75, game, 1));
	slider = new Slider(game, 200, 200);
}

void OptionsState::update()
{
}

void OptionsState::draw()
{
	slider->draw();
	for (auto b : getButtonsUI()) {
		b->draw();
	}
}

void OptionsState::next()
{

}

void OptionsState::registerCommands()
{
	commandFactory->add(new CommandExit());
	commandFactory->add(new CommandClick());

}
