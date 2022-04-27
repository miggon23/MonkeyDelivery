#pragma once
#include "../../Button.h"

class ExitButton :public Button {
public:
	ExitButton(int x, int y, double w, double h, Game* game);
	void onCursorCollision() override;
};
