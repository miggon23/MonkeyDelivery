#pragma once
#include "State.h"

class Shop;
class ShopState : public State
{
	Texture* panelTexture;
	
	int xObj=140, yObj=105, wObj=100, hObj=100, xOffset = 160, yOffset = 115;

	Shop* shop_;
	
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


