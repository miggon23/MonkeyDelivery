#pragma once
#include "Slider.h"

class BrightnessSlider :public Slider {
	const int TOP_VALUE_BRIGHTNESS = 122;
public:
	BrightnessSlider(Game* game, double x, double y);
	~BrightnessSlider();
	void Utility() override;
};