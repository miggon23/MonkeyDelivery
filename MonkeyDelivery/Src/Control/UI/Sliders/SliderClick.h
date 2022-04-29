#pragma once
#include "../../Button.h"
#include "../../../Logic/Game.h"

class SliderClick: public Button{
public:

	Texture* texture_;

	SliderClick(Game* game,double topPosition,double minPosition,double x, double y);
	~SliderClick() {};
	void update() override;
	void onCursorCollision() override;
	void move();
	inline bool onMoving() { return onMoving_; };
	inline void chageMaxPosition(double pos) { MAX_POSITION = pos; };
	inline void chageMinPosition(double pos) { MIN_POSITION = pos; };
	inline double MaxPosition() { return MAX_POSITION; };
	inline double MinPosition() { return MIN_POSITION; };
	
private:
    double MAX_POSITION;
	double MIN_POSITION;
	bool onMoving_ = false;
};