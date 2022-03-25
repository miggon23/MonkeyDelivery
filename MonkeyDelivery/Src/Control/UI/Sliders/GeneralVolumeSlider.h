#pragma once
#include"Slider.h"
class GeneralVolumeSlider :public Slider {
public:
	GeneralVolumeSlider(Game* game, double x, double y);
	~GeneralVolumeSlider();
	//El metodo de utility realiza la funcionalidad que queramos que cumpla ese slider
	void Utility() override;
};