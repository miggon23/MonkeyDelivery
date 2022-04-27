#pragma once

#include "../../Button.h"
class Game;

class Start : public Button {
public:
	Start(int x, int y,double w , double h,Game* game);
	~Start() {};
	void onCursorCollision() override;
};