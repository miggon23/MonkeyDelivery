#pragma once
#include"Slider.h"

class GeneralMusicSlider :public Slider {
public:
	GeneralMusicSlider(Game* game, double x, double y);
	~GeneralMusicSlider();
	//El metodo de utility realiza la funcionalidad que queramos que cumpla ese slider
	void Utility() override;
};