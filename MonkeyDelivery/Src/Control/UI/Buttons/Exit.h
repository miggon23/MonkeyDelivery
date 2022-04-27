#pragma once 
#include "../../Button.h"
class Game;

class Exit : public Button {
public:
	Exit(int x, int y, double w, double h, Game* game);
	~Exit() {};
	void onCursorCollision() override;
};