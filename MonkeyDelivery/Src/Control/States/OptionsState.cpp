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
	
	addButton(new Back((int)game->getWindowWidth() / 2 - buttonW/2, (int)game->getWindowHeight() - 250, buttonW, buttonH, game));
	
	addSlider(new GeneralVolumeSlider(game, game->getWindowWidth()/2 - 450, game->getWindowHeight()/4 - 50));
	addSlider(new BrightnessSlider(game, game->getWindowWidth() / 2 - 450, 450));
	addSlider(new GeneralMusicSlider(game, game->getWindowWidth() / 2 , game->getWindowHeight() / 4 - 50));
	addSlider(new GeneralSoundsEffectSlider(game, game->getWindowWidth() / 2, 450));
	backgroundTexture = game->getTexture(bckg_options);
	
	//signsTexture = game->getTexture(settingsSignsTexture);
	//settingsSignsTexture
}

void OptionsState::update(){
	sdlutils().musics().at("menumusic").setMusicVolume((int)(game->getMusicVolume() * game->getGeneralVolume()));
	for (auto b : getSlidersUI()) {
		b->update();
	}
}

void OptionsState::draw(){
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
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