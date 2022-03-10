#pragma once 

#include "../Button.h"
class Game;

class Options : public Button {
public:
	Options(int x, int y, int w, int h, Game* game, ViewController* v);
	~Options() {};
	void onCursorCollision() override;


};
