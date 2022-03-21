#include "Slider.h"
#include <iostream>
Slider::Slider(Game* game, double x, double y):game_(game){
	sliderBase_ = new SliderBase(game, x, y);
	sliderClick_ = new SliderClick(game, x + sliderBase_->getWidth(), x, y);
}

Slider::~Slider(){
	std::cout << "Slider Destruido" << std::endl;
	delete sliderClick_; sliderClick_ = nullptr;
	delete sliderBase_; sliderBase_ = nullptr;
	game_ = nullptr;
}

void Slider::draw(){
	sliderBase_->draw();
	sliderClick_->draw();
}

void Slider::update(){
	//aqui se valancea lo q haga el slid+er
}
