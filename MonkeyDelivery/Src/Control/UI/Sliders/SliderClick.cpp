#include "SliderClick.h"

SliderClick::SliderClick(Game* game, double topPosition,double minPosition ,double x, double y):
	Button(game,x,y),MAX_POSITION(topPosition),MIN_POSITION(minPosition ){
	setPosition(x, y);
}

void SliderClick::update(){
	if (onMoving_) {
		move();
	}
}

void SliderClick::move(){
	SDL_GetMouseState(&x_, &y_);	
	//std::cout << x_ << std::endl;	
	setPosition( x_-getWidth()/2, getPosition().getY());
	if (getPosition().getX() > MAX_POSITION+20)setPosition(MAX_POSITION, getPosition().getY());
	else if(getPosition().getX() <MIN_POSITION-20)setPosition(MIN_POSITION, getPosition().getY());
}

void SliderClick::onCursorCollision() {
	onMoving_ = !onMoving_;
	//std::cout << "onMoving: " << onMoving_ << std::endl;
}