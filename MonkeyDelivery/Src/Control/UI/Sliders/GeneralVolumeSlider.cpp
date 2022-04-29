#include "GeneralVolumeSlider.h"
#include "../../../Logic/Game.h"

GeneralVolumeSlider::GeneralVolumeSlider(Game* game, double x, double y):Slider(game,x,y){
	sliderClick_->setTexture(UI_Checker01);
}

void GeneralVolumeSlider::Utility(){
	double x = Percent();
	game_->ChangeGeneralVolume(x);
}