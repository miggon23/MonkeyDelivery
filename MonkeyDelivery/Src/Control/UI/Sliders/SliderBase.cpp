#include "SliderBase.h"
#include <iostream>
SliderBase::SliderBase(Game* game, int x, int y):GameObject(game){
	setTexture(sliderBase);
	setPosition(x, y);
}

SliderBase::~SliderBase(){
	std::cout << "SliderBase destruida" << std::endl;
}
