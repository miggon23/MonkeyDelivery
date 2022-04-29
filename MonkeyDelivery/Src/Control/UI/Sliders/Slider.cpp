#include "Slider.h"
#include <iostream>

Slider::Slider(Game* game, double x, double y) :game_(game) {
	sliderBase_ = new SliderBase(game, x, y);
	sliderClick_ = new SliderClick(game, x + sliderBase_->getWidth() / 2, y, x, y);
	setSize(384, 168);
}

Slider::~Slider() {
	std::cout << "Slider Destruido" << std::endl;
	delete sliderClick_; sliderClick_ = nullptr;
	delete sliderBase_; sliderBase_ = nullptr;
	game_ = nullptr;
}

void Slider::draw() {
	sliderBase_->draw();
	sliderClick_->draw();
}

void Slider::update() {
	sliderClick_->update();
	//si se mueve miro si ha cambiado el sliderclick de sitio y por tanto su funcionalidad tiene que realizarse
	if (sliderClick_->onMoving())
		Utility();
}

void Slider::setSize(int w, int h)
{
	sliderBase_->setDimension(w, h);
	sliderClick_->setDimension(108, 23);
	sliderClick_->setPosition(sliderBase_->getPosition().getX() + w / 2 , sliderBase_->getPosition().getY() + h / 2 - sliderClick_->getHeight()/2);
	sliderClick_->chageMaxPosition(sliderBase_->getPosition().getX() + sliderBase_->getWidth()- sliderClick_->getWidth());
	sliderClick_->chageMinPosition(sliderBase_->getPosition().getX());
}

double Slider::Percent() {
	double maxDistance = sliderClick_->MaxPosition() - sliderClick_->MinPosition();
	double x = sliderClick_->getPosition().getX() - sliderClick_->MinPosition();
	cout << x / maxDistance << endl;
	if (x / maxDistance < 0)return 0;
	else if (x / maxDistance > 1)return 1;

	return x / maxDistance;
}