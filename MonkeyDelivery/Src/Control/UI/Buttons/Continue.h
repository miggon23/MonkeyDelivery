#pragma once
#include "../../Button.h"

#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"

class Continue : public Button
{
public:
	Continue(int x, int y, double w, double h, Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Continue);
	};
	~Continue() {};
	inline void onCursorCollision() override { ChangeToLastState(); };
};