#pragma once

#include "../../Button.h"
class Game;

class Credits : public Button {
public:
	Credits(int x, int y, double w , double h,Game* game);
	~Credits() {};
	void onCursorCollision() override;
};
