#include "GeneralVolumeSlider.h"
#include "../../../Logic/Game.h"

GeneralVolumeSlider::GeneralVolumeSlider(Game* game, double x, double y):Slider(game,x,y){
}

GeneralVolumeSlider::~GeneralVolumeSlider(){
}

void GeneralVolumeSlider::Utility(){
	double x = 128 * Percent();
	game_->ChangeGeneralVolume(int(x));
}
