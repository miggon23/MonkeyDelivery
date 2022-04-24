#include "BrightnessSlider.h"
#include <SDL.h>
#include "../../../sdlutils/SDLUtils.h"

BrightnessSlider::BrightnessSlider(Game* game, double x, double y):Slider(game,x,y){
	sliderClick_->setPosition(sliderClick_->MaxPosition(), sliderClick_->getPosition().getY());
}

BrightnessSlider::~BrightnessSlider(){
}

void BrightnessSlider::Utility(){
	float x = (float)Percent();
	//game_->ChangeAlphaBrightness(int(x));*/	
	
	SDL_SetWindowBrightness(sdlutils().window(), x);
}