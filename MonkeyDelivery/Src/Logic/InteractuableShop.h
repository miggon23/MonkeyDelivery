#pragma once
#include "GameObject.h"
class IntectuableShop:public GameObject
{
	bool active = false;
public:
	IntectuableShop(Game* game,int x, int y);
	~IntectuableShop();
	void update() override;
	void onPlayerInteraction(Player* player) override;
};

