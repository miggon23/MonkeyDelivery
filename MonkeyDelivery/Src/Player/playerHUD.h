#pragma once

#include "../Logic/GameObject.h"
class Game;

class playerHUD: public GameObject {
private:

	Texture* HUD_Base;
	Texture* HUD_Fill;
	SDL_Rect baseRect_;
	
public:
	playerHUD(Game* game);
	~playerHUD() { };

	void update() override {};
	void drawFillHUD();
	void drawOverHUD();
};