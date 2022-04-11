#pragma once
#include "State.h"

class Shop;
class ShopState : public State
{	
public:
	ShopState(Game* game);
	~ShopState();

	void update()override;
	void draw ()override;
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

	const int xObj = 420, yObj = 300, wObj = 405, hObj = 512, xOffset = 90, yOffset = 250, //Valores para el Hito2
		
	xText = 680, yText = 830; //Coordenadas  para el Hito2
	const int MAX_SELECTED = 8, FAIL_TIMESHOWED = 3000;

	int selected_ = 0, lastClicked_;	
	bool closeFailed_ = false;
	string textError_;

	Shop* shop_;
	Font* font_;
};