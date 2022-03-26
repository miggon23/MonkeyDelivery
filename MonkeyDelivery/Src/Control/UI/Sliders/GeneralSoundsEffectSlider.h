#pragma once
#include"Slider.h"
class GeneralSoundsEffectSlider :public Slider {
public:
	GeneralSoundsEffectSlider(Game* game, double x, double y);
	~GeneralSoundsEffectSlider();
	//El metodo de utility realiza la funcionalidad que queramos que cumpla ese slider
	void Utility() override;
};