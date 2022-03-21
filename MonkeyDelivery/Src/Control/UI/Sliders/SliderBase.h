#pragma once
#include "../../../Logic/GameObject.h"
class SliderBase: public GameObject{
public:
	SliderBase(Game* game, int x, int y);
	~SliderBase();
	void update() override{};

};

