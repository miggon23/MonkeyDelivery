#pragma once
#include "GameObject.h"
class IntectuableShop:public GameObject
{
	Texture* itemsTex_;
public:
	IntectuableShop(Game* game,int x, int y);
	~IntectuableShop();
	void update() override;
	void draw() override;

	void onPlayerInteraction(Player* player) override;
};