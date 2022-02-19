#pragma once
#include "Command.h"

class CommandInteract : public Command
{
public:
	CommandInteract() {};
	~CommandInteract() = default;

	bool parse(SDL_Event & event) override;
	void execute() override;
};

