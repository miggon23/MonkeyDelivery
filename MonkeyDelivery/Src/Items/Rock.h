#pragma once
#include "../Logic/ColliderTile.h"

class Rock : public ColliderTile {
	int w=75.0;
	int h=75.0;
public:
	Rock(Game* game, int x, int y);
	~Rock();	
	void draw() override;
	//void onPlayerInteraction(Player* player) override;
};