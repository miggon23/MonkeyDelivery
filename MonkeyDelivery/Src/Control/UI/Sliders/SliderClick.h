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
	inline void chageMaxPosition(double pos) { MAX_POSITION = pos; };
private:
    double MAX_POSITION;
	bool onMoving_ = false;
};

