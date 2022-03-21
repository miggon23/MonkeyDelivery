#pragma once
#include "../../../Logic/GameObject.h"
#include "../../../Logic/Game.h"

class SliderClick: public GameObject{
public:
	SliderClick(Game* game,double topPosition,double x, double y);
	~SliderClick();
	 void update() override;
	 void move(double x);
private:
	const double MAX_POSITION;
};

