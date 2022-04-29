#include "GeneralMusicSlider.h"
#include "../../../Logic/Game.h"

GeneralMusicSlider::GeneralMusicSlider(Game* game, double x, double y):Slider(game,x,y){
	sliderClick_->setTexture(UI_Checker02);
}

GeneralMusicSlider::~GeneralMusicSlider(){
}

void GeneralMusicSlider::Utility(){
	double x = 128 * Percent();
	game_->ChangeMusicVolume(int(x));
}