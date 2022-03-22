#include "SliderClick.h"

SliderClick::SliderClick(Game* game, double topPosition, double x, double y):Button(game,x,y),MAX_POSITION(topPosition){
	setTexture(sliderClicker);
	setPosition(x, y);
}

SliderClick::~SliderClick(){
}

void SliderClick::update(){
	if (onMoving_) {
		move();
	}
}

void SliderClick::move(){
	if (getPosition().getX() + 0.5f < MAX_POSITION) {
		setPosition(getPosition().getX() + 0.5f, getPosition().getY());
	}
}

void SliderClick::onCursorCollision() {
	onMoving_ = !onMoving_;
	std::cout << "onMoving: " << onMoving_ << std::endl;
}

