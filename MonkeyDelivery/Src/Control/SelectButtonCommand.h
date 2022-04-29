#pragma once
#include "Command.h"
#include "../Logic/Game.h"
#include "States/State.h"
#include "States/MenuState.h"

class SelectButtonCommand : public Command
{
public:
	SelectButtonCommand(State* mS);
	~SelectButtonCommand() = default;
	
	bool parse(SDL_Event& event) override;
	void execute() override;

private:
	Vector2D<int> move;
	State* state;
};

