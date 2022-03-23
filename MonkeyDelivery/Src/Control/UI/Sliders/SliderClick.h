#pragma once
#include "../../Button.h"
#include "../../../Logic/Game.h"

class SliderClick: public Button{
public:
	SliderClick(Game* game,double topPosition,double minPosition,double x, double y);
	~SliderClick();
	void update() override;
	void onCursorCollision() override;
	void move();
	inline void chageMaxPosition(double pos) { MAX_POSITION = pos; };
	inline void chageMinPosition(double pos) { MIN_POSITION = pos; };
private:
    double MAX_POSITION;
	double MIN_POSITION;
	bool onMoving_ = false;
};

