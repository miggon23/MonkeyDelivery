#pragma once

#include "../../Button.h"
class Game;

class Menu : public Button
{
public:
	Menu(int x, int y, double w, double h, Game* game);
	~Menu() {};
	void onCursorCollision() override;
};

