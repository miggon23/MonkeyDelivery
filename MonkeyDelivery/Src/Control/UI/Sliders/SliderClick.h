#pragma once
#include "../../Button.h"
#include "../../../Logic/Game.h"

class SliderClick: public Button{
public:
	SliderClick(Game* game,double topPosition,double x, double y);
	~SliderClick();
	void update() override;
	void onCursorCollision() override;
	void move();
private:
	const double MAX_POSITION;
	bool onMoving_ = false;
};

