#pragma once
#include "State.h"

class ShopState : public State
{
public:
	ShopState(Game* game);
	~ShopState() = default;

	void update()override;
	void draw()override;
	void next()override;

	string getStateName() const {
		return "Pause state";
	};

	void registerCommands()override;
};


