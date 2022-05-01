#pragma once
#include "GameObject.h"
class IntectuableShop:public GameObject
{
public:
	IntectuableShop(Game* game,int x, int y, AnimationManager* anim);
	~IntectuableShop();
	void update() override;
	void draw() override;

	void onPlayerInteraction(Player* player) override;
};