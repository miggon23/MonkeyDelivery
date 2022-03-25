#include "OptionsState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../UI/Buttons/Back.h"
#include "../UI/Buttons/Back1.h"
#include "../UI/Sliders/Slider.h"
#include "../UI/Sliders/GeneralVolumeSlider.h"
OptionsState::OptionsState(Game* game, int num) : State(game){
	registerCommands();
	if (num == 1)
	addButton(new Back(game->getWindowWidth() / 2 - 50, game->getWindowHeight() - 250, 100, 75, game));
	else 	
		addButton(new Back1(game->getWindowWidth() / 2 - 50, game->getWindowHeight() - 250, 100, 75, game));

	addSlider(new GeneralVolumeSlider(game, 200, 200));
	slidersUI[0]->setSize(300, 150);
}

void OptionsState::update(){
	for (auto b : getSlidersUI()) {
		b->update();
	}
}

void OptionsState::draw(){
	for (auto b : getButtonsUI()) {
		b->draw();
	}
	for (auto b : getSlidersUI()) {
		b->draw();
	}
}

void OptionsState::next(){

}

void OptionsState::registerCommands(){
	commandFactory->add(new CommandExit());
	commandFactory->add(new CommandClick());
}
