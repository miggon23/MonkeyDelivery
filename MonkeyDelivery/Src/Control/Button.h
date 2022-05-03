#pragma once

#include "../Logic/GameObject.h"
#include "../Control/ViewController.h"
class Game;

class Button : public GameObject {
protected:
	int x_;
	int y_;

public:
	Button(Game* game, double wight, double height, int x, int y);
	Button(Game* game, int x, int y);
	~Button() { };
	bool onClick();
	virtual void  update() override;
    virtual void onCursorCollision()=0;
	
	void ChangeToNewState(State* state,bool guardar);
	void ChangeToLastState();

	void ChangeToOptionsState();
	void ChangeToLastaStateNO_DELETE_LAST();
};