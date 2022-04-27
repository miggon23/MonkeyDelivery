#pragma once
#include "Command.h"
#include "../Logic/Game.h"
#include "States/MenuState.h"

class SelectButtonCommand : public Command
{
public:
	SelectButtonCommand(MenuState* mS);
	~SelectButtonCommand() = default;
	
	bool parse(SDL_Event& event) override;
	void execute() override;

private:
	int move;
	MenuState* menuState;
};

