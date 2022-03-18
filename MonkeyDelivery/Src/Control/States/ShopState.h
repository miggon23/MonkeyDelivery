#pragma once
#include "State.h"

class Shop;
class ShopState : public State
{
	Texture* panelTexture;
	
	const int xObj=140, yObj=105, wObj=100, hObj=100, xOffset = 160, yOffset = 115,
		xText = 260, yText = 320;
	int selected_ = 0;

	Shop* shop_;
	Font* font_;
	
public:
	ShopState(Game* game);
	~ShopState();

	void update()override;
	void draw()override;
	void next()override;

	string getStateName() const {
		return "Shop state";
	};

	void registerCommands()override;

	void moveSelected(int to);
};


