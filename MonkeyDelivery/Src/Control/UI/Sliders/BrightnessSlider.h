#pragma once
#include "Slider.h"

class BrightnessSlider :public Slider {
public:
	BrightnessSlider(Game* game, double x, double y);
	~BrightnessSlider();
	void Utility() override;
};