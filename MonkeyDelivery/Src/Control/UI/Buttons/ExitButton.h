#pragma once
#include "../../Button.h"

class ExitButton :public Button {
public:
	ExitButton(int x, int y, int w, int h, Game* game);
	void onCursorCollision() override;
};
