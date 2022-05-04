#include "GeneralVolumeSlider.h"
#include "../../../Logic/Game.h"

GeneralVolumeSlider::GeneralVolumeSlider(Game* game, double x, double y):Slider(game,x,y){
	sliderClick_->chageMaxPosition(sliderClick_->MaxPosition() + 30);
	sliderClick_->chageMinPosition(sliderClick_->MinPosition() + 28);
	sliderClick_->setTexture(UI_Checker01);
	sliderClick_->setPosition(sliderClick_->getX()-sliderClick_->getWidth()/4, sliderClick_->getPosition().getY() - 20);
	sliderClick_->setDimension(60, 65);
}

void GeneralVolumeSlider::Utility(){
	double x = Percent();
	game_->ChangeGeneralVolume(x);
}