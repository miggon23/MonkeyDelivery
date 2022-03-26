#include "GeneralMusicSlider.h"
#include "../../../Logic/Game.h"

GeneralMusicSlider::GeneralMusicSlider(Game* game, double x, double y):Slider(game,x,y){
}

GeneralMusicSlider::~GeneralMusicSlider(){
}

void GeneralMusicSlider::Utility(){
	double x = 128 * Percent();
	game_->ChangeGeneralVolume(int(x));
}
