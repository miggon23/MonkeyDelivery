#pragma once
#include "Command.h"
class CommandMoveV :public Command
{
	int dir = 0;
public:
	CommandMoveV() {};
	~CommandMoveV() = default;

	bool parse(SDL_Event & event) override;
	void execute() override;
};

