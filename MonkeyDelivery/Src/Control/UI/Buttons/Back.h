#pragma once

#include "../../Button.h"
class Game;

class Back : public Button {

public:
	Back(int x, int y,double w ,double h,Game* game);
	~Back() {};
	void onCursorCollision() override;
};
