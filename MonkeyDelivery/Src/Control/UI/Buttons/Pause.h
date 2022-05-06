#pragma once

#include "../../Button.h"
#include "../../../Logic/Game.h"
#include "../../States/PauseState.h"
class Game;

class Pause : public Button {

public:
	Pause(int x, int y, double w , double h,Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Pause);
	};
	~Pause() {};
	inline void onCursorCollision() override { ChangeToNewState(new PauseState(game), true); };
};