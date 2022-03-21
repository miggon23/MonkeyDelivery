#include "SliderClick.h"

SliderClick::SliderClick(Game* game, double topPosition, double x, double y):GameObject(game),MAX_POSITION(topPosition){
	setTexture(sliderClicker);
	setPosition(x, y);
}

SliderClick::~SliderClick(){
}

void SliderClick::update(){
}

void SliderClick::move(double x){
	if (getPosition().getX() + x < MAX_POSITION) {
		setPosition(getPosition().getX() + x, getPosition().getY());
	}
}
