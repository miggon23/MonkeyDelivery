#pragma once
#include "GameObject.h"
class IntectuableShop:public GameObject
{
	Texture* itemsTex_;
	Texture* sellerTex_;
	float timerAnimation2_;
	int time2_;
	SDL_Rect dest;
public:
	IntectuableShop(Game* game,int x, int y);
	~IntectuableShop();
	void update() override;
	void draw() override;

	void onPlayerInteraction(Player* player) override;
};