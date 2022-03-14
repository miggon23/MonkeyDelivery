#pragma once
#include "GameObject.h"
class IntectuableShop:public GameObject
{
	bool active = false;
public:
	IntectuableShop(Game* game);
	~IntectuableShop();
	void update() override;
	void onPlayerInteraction(Player* player) override;
};

