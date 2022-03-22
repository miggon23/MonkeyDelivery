#include "OptionsState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../CommandOnClick.h"
#include "../UI/Buttons/Back.h"

OptionsState::OptionsState(Game* game) : State(game)
{
	registerCommands();
	addButton(new Back(game->getWindowWidth() / 2 - 100, game->getWindowHeight() - 250, 100, 75, game, 1));
	addSlider(new Slider(game, 200, 200));
	//slidersUI[0]->setSize(400, 200);
}

void OptionsState::update(){
	for (auto b : getSlidersUI()) {
		b->update();
	}
}

void OptionsState::draw()
{
	for (auto b : getButtonsUI()) {
		b->draw();
	}
	for (auto b : getSlidersUI()) {
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
	commandFactory->add(new CommandOnClick());
}
