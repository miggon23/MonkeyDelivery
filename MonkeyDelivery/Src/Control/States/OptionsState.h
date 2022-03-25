#pragma once
#include "State.h"
#include "../../Logic/Game.h"
#include "../States/MenuState.h"
class OptionsState : public State
{
public:
	OptionsState(Game* game, int num);
	~OptionsState() = default;

	void update()override;
	void draw()override;
	void next()override;

	string getStateName() const {
		return "Options state";
	};

	void registerCommands()override;
};


