#pragma once
#include "../Logic/GameObject.h"
class Bed:public GameObject
{
	bool active = false;
public:
	Bed(Game* game);
	Bed(Game* game, int x, int y);
	~Bed();
	void update() override;
	void onPlayerInteraction(Player* player) override;
};