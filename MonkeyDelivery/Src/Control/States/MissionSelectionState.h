#pragma once

#include "PauseState.h"

class MissionSelectionState : public PauseState
{
public:
	MissionSelectionState(Game* game);
	~MissionSelectionState();

	void draw() override;
private:
	Texture* background_;

};

