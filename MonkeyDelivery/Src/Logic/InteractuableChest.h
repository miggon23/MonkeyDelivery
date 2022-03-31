#pragma once
#include "GameObject.h"
class InteractuableChest : public GameObject
{
	const int x = 100,
		y = 50,
		w = 600,
		h = 800;

	bool active = false;
	Texture* rewardT_;
public:
	InteractuableChest(Game* game, int x, int y, int w, int h);
	~InteractuableChest() = default;

	void draw() override;
	void update() override {};

	void onPlayerInteraction(Player* player) override;

	void selectReward(int reward, Player* player);
};

