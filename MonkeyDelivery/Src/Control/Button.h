#pragma once

#include "../Logic/GameObject.h"
#include "../Control/ViewController.h"
class Game;

class Button : public GameObject {
private:

	int x_;
	int y_;
	SDL_Event* event;

protected:
	ViewController* v_;
public:
	Button(Game* game, int wight, int height, int x, int y, ViewController* v);
	~Button() { };

	void update() override;
    virtual void onCursorCollision()=0;
	//bool parse(SDL_Event& event);

};
