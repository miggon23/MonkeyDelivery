#include "OptionsState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../UI/Buttons/Back.h"
#include "../UI/Buttons/Back1.h"
#include "../UI/Sliders/Slider.h"
#include "../UI/Sliders/GeneralVolumeSlider.h"
#include "../UI/Sliders/GeneralSoundsEffectSlider.h"
#include "../UI/Sliders/GeneralMusicSlider.h"
#include "../UI/Sliders/BrightnessSlider.h"

OptionsState::OptionsState(Game* game/*, int num*/) : State(game){
	registerCommands();
	
	addButton(new Back(game->getWindowWidth() / 2 - 50, game->getWindowHeight() - 250, 100, 75, game));
	
	addSlider(new GeneralVolumeSlider(game, 200, 200));
	addSlider(new BrightnessSlider(game, 200, 500));
	addSlider(new GeneralMusicSlider(game, 1000, 200));
	addSlider(new GeneralSoundsEffectSlider(game, 1000, 500));

	backgroundTexture = game->getTexture(button_Main_Options);
	//signsTexture = game->getTexture(settingsSignsTexture);
	//settingsSignsTexture
}

void OptionsState::update(){
	sdlutils().musics().at("menumusic").setMusicVolume(game->getMusicVolume() * game->getGeneralVolume());
	for (auto b : getSlidersUI()) {
		b->update();
	}
}

void OptionsState::draw(){
	SDL_Rect rectPanel = { 0,0,game->getWindowWidth(),game->getWindowHeight() };
	backgroundTexture->render(rectPanel);
	/*rectPanel = { 100,100,200,400 };
	signsTexture->render(rectPanel);*/
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
	commandFactory->add(new CommandClick());
	//commandFactory->add(new CommandExit());
}