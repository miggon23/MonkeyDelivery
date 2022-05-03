#pragma once
#include "../../../Logic/GameObject.h"

class SliderBase: public GameObject{
public:
	SliderBase(Game* game, double x, double y);
	~SliderBase();
	void update() override{};

};