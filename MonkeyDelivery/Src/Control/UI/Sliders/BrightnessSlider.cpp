#include "BrightnessSlider.h"
#include <SDL.h>
#include "../../../sdlutils/SDLUtils.h"

BrightnessSlider::BrightnessSlider(Game* game, double x, double y):Slider(game,x,y){
	sliderClick_->chageMaxPosition(sliderClick_->MaxPosition() + 40);
	sliderClick_->chageMinPosition(sliderClick_->MinPosition() + 35);
	sliderClick_->setPosition(sliderClick_->MaxPosition(), sliderClick_->getPosition().getY()-5);
	sliderClick_->setTexture(UI_Checker03);
	sliderClick_->setDimension(35, 35);
}

BrightnessSlider::~BrightnessSlider(){
}

void BrightnessSlider::Utility(){
	float x = (float)Percent();
	
	SDL_SetWindowBrightness(sdlutils().window(), x);
}