#pragma once

#include "../../Button.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"
class Game;

class Back1 : public Button {

public:
	Back1(int x, int y,double w ,double h,Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Back);
	};
	~Back1() {};
	inline void onCursorCollision() override { ChangeToLastState(); };
};
