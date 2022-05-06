#pragma once

#include "../../Button.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"

class Game;

class Menu : public Button
{
public:
	Menu(int x, int y, double w, double h, Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Back);
	};
	~Menu() {};
	inline void onCursorCollision() override {
		game->clearSavedState();
		ChangeToNewState(new MenuState(game), false);
	};
};

