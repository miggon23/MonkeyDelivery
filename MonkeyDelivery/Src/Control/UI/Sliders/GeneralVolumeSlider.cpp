#include "GeneralVolumeSlider.h"
#include "../../../Logic/Game.h"

GeneralVolumeSlider::GeneralVolumeSlider(Game* game, double x, double y):Slider(game,x,y){
}

void GeneralVolumeSlider::Utility(){
	double x = Percent();
	game_->ChangeGeneralVolume(x);
}