#pragma once
#include "Command.h"
class FastTextCommand : public Command
{
public:
	FastTextCommand() {};
	~FastTextCommand() = default;

	bool parse(SDL_Event & event) override;
	void execute() override;
};




