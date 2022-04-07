#pragma once 
#include "../../Button.h"
class Game;

class Exit : public Button {
public:
	Exit(int x, int y, int w, int h, Game* game);
	~Exit() {};
	void onCursorCollision() override;
};