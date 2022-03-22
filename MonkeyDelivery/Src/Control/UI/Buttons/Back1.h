#pragma once

#include "../../Button.h"
class Game;

class Back1 : public Button {

public:
	Back1(int x, int y,int w , int h,Game* game);
	~Back1() {};
	void onCursorCollision() override;
};
