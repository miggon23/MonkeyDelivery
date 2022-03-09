#pragma once

#include "../Logic/GameObject.h"
class Game;

class Button : public GameObject {
private:

	int x_;
	int y_;

public:
	Button(Game* game, int wight, int height, int x, int y);
	~Button() { };

	void update() override;
    virtual void onCursorCollision()=0;

};
