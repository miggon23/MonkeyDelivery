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
private:
	Game* game_;
	//Necesitamos una parte de panel y la otra parte clicable
	SliderClick* sliderClick_;
	SliderBase* sliderBase_;
};

