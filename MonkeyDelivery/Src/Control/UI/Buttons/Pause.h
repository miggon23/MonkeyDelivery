#pragma once

#include "../../Button.h"
class Game;

class Pause : public Button {

public:
	Pause(int x, int y, double w , double h,Game* game);
	~Pause() {};
	void onCursorCollision() override;
};