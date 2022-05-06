#pragma once

#include "../../Button.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"

class Game;

class Back : public Button {

public:
	Back(int x, int y,double w ,double h,Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Back);
	};
	~Back() {};
	inline void onCursorCollision() override { ChangeToLastaStateNO_DELETE_LAST(); }
};