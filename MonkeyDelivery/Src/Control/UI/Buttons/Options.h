#pragma once 

#include "../../Button.h"
class Game;

class Options : public Button {

	int num_;

public:
	Options(int x, int y, double w, double h, Game* game, int num);
	~Options() {};
	void onCursorCollision() override;
};