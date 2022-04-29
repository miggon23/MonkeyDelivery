#include "GeneralSoundsEffectSlider.h"
#include "../../../Logic/Game.h"

GeneralSoundsEffectSlider::GeneralSoundsEffectSlider(Game* game, double x, double y):Slider(game,x,y){

	sliderClick_->chageMaxPosition(sliderClick_->MaxPosition() + 30);
	sliderClick_->chageMinPosition(sliderClick_->MinPosition() + 15);
	sliderClick_->setPosition(sliderClick_->MaxPosition(), sliderClick_->getPosition().getY() - 25);
	sliderClick_->setTexture(UI_Checker00);
	sliderClick_->setDimension(70, 70);
}

void GeneralSoundsEffectSlider::Utility(){
	double x = 128 * Percent();
	game_->ChangeSoundEfectsVolume(int(x));
}