#include "BrightnessSlider.h"

BrightnessSlider::BrightnessSlider(Game* game, double x, double y):Slider(game,x,y){
}

BrightnessSlider::~BrightnessSlider(){
}

void BrightnessSlider::Utility(){
	double x = TOP_VALUE_BRIGHTNESS * Percent();
	game_->ChangeAlphaBrightness(int(x));
}
