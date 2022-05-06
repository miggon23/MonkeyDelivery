#pragma once

#include "../../Button.h"
#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"
#include "../../States/CreditsState.h"
class Game;

class Credits : public Button {
public:
	Credits(int x, int y, double w , double h,Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Main_Credits);
	};
	~Credits() {};
	inline void onCursorCollision() override { ChangeToNewState(new CreditsState(game), true); };
};
