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

	void moveSelected(int to);

	void buySelected();

private:
	Texture* panelTexture;

	const int xObj = 128, yObj = 105, wObj = 100, hObj = 100, xOffset = 160, yOffset = 115,
		xText = 260, yText = 320;
	int selected_ = 0;

	Shop* shop_;
	Font* font_;
};


