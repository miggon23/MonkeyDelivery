#pragma once
#include "GameObject.h"
class InteractuableChest : public GameObject
{
	int selection_;
	double x_, y_, w_, h_;
	float timer_;
	bool active = false;
	double limit = 4000, semiLimit=(limit/2.0);
	Texture* rewardT_;
public:
	InteractuableChest(Game* game, int x, int y, int w, int h, int select);
	~InteractuableChest() {
		rewardT_ = nullptr;
	};

	void draw() override;
	void update() override {};

	void onPlayerInteraction(Player* player) override;

	void selectReward(int reward, Player* player);
};