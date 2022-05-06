#pragma once
#include "../../Button.h"

class ExitButton :public Button {
public:
	ExitButton(int x, int y, double w, double h, Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Main_ExitButton);
	};
	void onCursorCollision() override { game->setUserExit(); };
};
