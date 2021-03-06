#pragma once

#include "../../Button.h"
#include "../../../Logic/Game.h"
#include "../../States/PlayingState.h"

class Game;

class Start : public Button {
public:
	Start(int x, int y,double w , double h,Game* game) :Button(game, w, h, x, y) {
		setTexture(button_Main_StartButton);
	};
	~Start() {};
	inline void onCursorCollision() override {
		sdlutils().musics().at("menumusic").pauseMusic();
		ChangeToNewState(new PlayingState(game), false);
	};
};