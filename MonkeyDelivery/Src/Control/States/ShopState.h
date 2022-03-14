#pragma once
#include "State.h"

class ShopState : public State
{
	Texture* panelTexture;
	int xPanel=100, yPanel=50, wPanel=500, hPanel=250;
	int xObj=100, yObj=50, wObj=500, hObj=250;
	
public:
	ShopState(Game* game);
	~ShopState();

	void update()override;
	void draw()override;
	void next()override;

	string getStateName() const {
		return "Pause state";
	};

	void registerCommands()override;
};


