#pragma once
#include "GameObject.h"
class InteractuableCarrot : public GameObject
{
	const int x = 100,
		y = 50,
		w = 600,
		h = 800;

	bool active = false;
	Texture* rewardT_;
public:
	InteractuableCarrot(Game* game, int x, int y, int w, int h);
	~InteractuableCarrot() {
		rewardT_ = nullptr;
	};

	void draw() override;
	void update() override {};

	void onPlayerInteraction(Player* player) override;

	void selectReward(int reward, Player* player);
};