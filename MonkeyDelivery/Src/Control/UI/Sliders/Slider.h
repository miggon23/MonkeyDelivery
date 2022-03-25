#pragma once
#include "SliderClick.h"
#include "SliderBase.h"
class Slider
{
public:
	Slider(Game* game,double x, double y);
	~Slider();
	void draw();	
	void update();
	void setSize(int w, int h);
	inline SliderClick* getSliderClick() { return sliderClick_; };
	inline SliderBase* getSliderBase() { return sliderBase_; };
	inline double getMinPosition() { return sliderBase_->getPosition().getX() - sliderBase_->getWidth() / 2; };
	double Percent();
	//El metodo de utility realiza la funcionalidad que queramos que cumpla ese slider
	virtual void Utility() = 0;
protected:
	Game* game_;
	//Necesitamos una parte de panel y la otra parte clicable
	SliderClick* sliderClick_;
	SliderBase* sliderBase_;
};

