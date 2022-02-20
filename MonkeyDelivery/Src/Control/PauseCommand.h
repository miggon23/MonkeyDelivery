#pragma once
#include "Command.h"

class PauseCommand : public Command
{

public:
	const string INFO_STRING = "[p] to pause the game";

	PauseCommand();
	~PauseCommand() = default;

	bool parse(SDL_Event& event) override;
	void execute() override;
};
