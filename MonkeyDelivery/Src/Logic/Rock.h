#pragma once
#include "GameObject.h"

class Rock : public GameObject {
public:
	Rock(Game* game, int x, int y);
	~Rock();
	void update() override;
};