#pragma once

#include "State.h"

class MissionSelectionState : public State
{
public:
	MissionSelectionState(Game* game);
	~MissionSelectionState();

	void draw() override;
	void update() override;
	void next() override;

	string getStateName() const {
		return "Mission Selection state";
	};

	void registerCommands()override;

private:
	Texture* background_;

};

