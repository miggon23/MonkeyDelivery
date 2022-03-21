#pragma once

#include "../../Button.h"
class Game;

class Pause : public Button {

public:
	Pause(int x, int y,int w , int h,Game* game);
	~Pause() {};
	void onCursorCollision() override;
};
