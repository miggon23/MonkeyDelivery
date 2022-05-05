#pragma once
#include "GameObject.h"
#include "AnimationManager.h"

class EndGameTarget : public GameObject
{
public:
	EndGameTarget(Game* g, AnimationManager* animation);
	~EndGameTarget();

	void onPlayerInteraction(Player* player) override;
	void draw() override;

	void update() override {};
};

