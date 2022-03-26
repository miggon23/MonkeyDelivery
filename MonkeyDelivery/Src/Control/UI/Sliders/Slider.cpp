#include "Slider.h"
#include <iostream>
Slider::Slider(Game* game, double x, double y):game_(game){
	sliderBase_ = new SliderBase(game, x, y);
	sliderClick_ = new SliderClick(game, x + sliderBase_->getWidth()/2, x /*- sliderBase_->getWidth()*/, x, y);
	setSize(300, 150);
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
	/*sliderBase_->drawDebug();
	sliderClick_->drawDebug();*/
}

void Slider::update(){
	sliderClick_->update();
	//si se mueve miro si ha cambiado el sliderclick de sitio y por tanto su funcionalidad tiene que realizarse
	if(sliderClick_->onMoving())
		Utility();
}

void Slider::setSize(int w, int h)
{
	sliderBase_->setDimension(w, h);
	sliderClick_->setDimension(w/2, h/2);
	sliderClick_->setPosition(sliderClick_->getX(),sliderBase_->getY()+sliderBase_->getWidth()/8);
	sliderClick_->chageMaxPosition(sliderBase_->getPosition().getX() + sliderBase_->getWidth()/2);
	sliderClick_->chageMinPosition(sliderBase_->getPosition().getX() /*- sliderBase_->getWidth()*/);
}

double Slider::Percent(){
	double maxDistance = sliderClick_->MaxPosition() - sliderClick_->MinPosition();
	double x= sliderClick_->getPosition().getX()-sliderClick_->MinPosition();	
	//cout << x/maxDistance<< endl;
	return x / maxDistance;
}
