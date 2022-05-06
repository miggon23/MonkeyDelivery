#pragma once 

#include "../../Button.h"
#include "../../../Logic/Game.h"
#include "../../States/OptionsState.h"
class Game;

class Options : public Button {

	int num_;

public:
	Options(int x, int y, double w, double h, Game* game, int num) :Button(game, w, h, x, y) {
		setTexture(button_Main_Options);
		num_ = num;
	};
	~Options() {};
	inline void onCursorCollision() override { ChangeToOptionsState(); }
};