#include "GeneralMusicSlider.h"
#include "../../../Logic/Game.h"

GeneralMusicSlider::GeneralMusicSlider(Game* game, double x, double y):Slider(game,x,y){
	sliderClick_->chageMaxPosition(sliderClick_->MaxPosition() + 40);
	sliderClick_->chageMinPosition(sliderClick_->MinPosition() + 32);
	sliderClick_->setPosition(sliderClick_->MaxPosition(), sliderClick_->getPosition().getY() - 15);
	sliderClick_->setTexture(UI_Checker02);
	sliderClick_->setDimension(50, 50);
}

void GeneralMusicSlider::Utility(){
	double x = 128 * Percent();
	game_->ChangeMusicVolume(int(x));
}