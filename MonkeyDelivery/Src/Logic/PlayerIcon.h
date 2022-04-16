#pragma once
#include "GameObject.h"

class PlayerIcon :public GameObject {
public:
	PlayerIcon(Game* game);
	~PlayerIcon() = default;
	void update() override {}
};