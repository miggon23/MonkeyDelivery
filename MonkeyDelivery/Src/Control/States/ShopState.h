#pragma once
#include "State.h"

class Shop;
class ShopState : public State
{	
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

	void moveSelectedX(int to);
	void moveSelectedY(int to);
	void buySelected();

private:
	Texture* panelTexture;

	const int xObj = 128, yObj = 105, wObj = 100, hObj = 100, xOffset = 160, yOffset = 115,
		xText = 260, yText = 320;
	const int MAX_SELECTED = 8;
	int selected_ = 0;	
	Shop* shop_;
	Font* font_;
};


