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
	Texture* controlsTexture;
	Texture* coinTexture;

	int xObj = 420, yObj = 300, wObj = 405, hObj = 512, xOffset = 90, yOffset = 250, //Valores para el Hito2
		
	xText = 680, yText = 830, maxSelected; //Coordenadas  para el Hito2
	const int FAIL_TIMESHOWED = 3000;

	int buttonsX_;
	int buttonsY_;
	int buttonsW_;
	int buttonsH_;	
	int coinsX_;
	int coinsY_;
	int coinsW_;
	int coinsH_;

	int selected_ = 0, lastClicked_;	
	bool closeFailed_ = false;
	string textError_;

	Shop* shop_;
	Font* font_;
};