#pragma once
#include "State.h"

class PauseState : public State
{
	Texture* backgroundTexture;
public:
	PauseState(Game* game);
	~PauseState() = default;

	void update()override;
	void draw()override;
	void next()override;

	string getStateName() const {
		return "Pause state";
	};

	void registerCommands()override;
};


