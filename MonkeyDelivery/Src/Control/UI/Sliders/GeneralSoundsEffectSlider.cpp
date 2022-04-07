#include "GeneralSoundsEffectSlider.h"
#include "../../../Logic/Game.h"

GeneralSoundsEffectSlider::GeneralSoundsEffectSlider(Game* game, double x, double y):Slider(game,x,y){
}

GeneralSoundsEffectSlider::~GeneralSoundsEffectSlider(){
}

void GeneralSoundsEffectSlider::Utility(){
	double x = 128 * Percent();
	game_->ChangeSoundEfectsVolume(int(x));
}