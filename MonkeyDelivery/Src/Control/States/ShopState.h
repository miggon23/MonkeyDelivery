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

	/*const int xObj = 128, yObj = 105, wObj = 100, hObj = 100, xOffset = 160, yOffset = 115,*/
	const int xObj = 200, yObj = 300, wObj = 200, hObj = 200, xOffset = 400, yOffset = 300, //Valores para el Hito2
		/*xText = 260, yText = 320;*/
		xText = 680, yText = 830; //Coordenadas  para el Hito2
	const int MAX_SELECTED = 8, FAIL_TIMESHOWED = 3000;

	int selected_ = 0, lastClicked_;	
	bool closeFailed_ = false;
	string textError_;

	Shop* shop_;
	Font* font_;
};


