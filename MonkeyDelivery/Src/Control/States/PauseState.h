#pragma once
#include "State.h"

class PauseState : public State
{
	Texture* backgroundTexture;
	const int buttonW = 300, buttonH = 140;
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