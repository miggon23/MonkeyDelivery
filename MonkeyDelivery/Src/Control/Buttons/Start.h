#pragma once

#include "../Button.h"
class Game;

class Start : public Button {
public:
	Start(int x, int y,int w , int h,Game* game, ViewController* v);
	~Start() {};
	void onCursorCollision() override;
};
