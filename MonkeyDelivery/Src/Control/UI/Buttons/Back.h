#pragma once

#include "../../Button.h"
class Game;

class Back : public Button {

	int num_;

public:
	Back(int x, int y,int w , int h,Game* game, int num);
	~Back() {};
	void onCursorCollision() override;
};
