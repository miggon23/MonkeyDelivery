#pragma once
#include "Command.h"
class InteractDialogueBoxCommand : public Command
{
public:
	InteractDialogueBoxCommand() {};
	~InteractDialogueBoxCommand() = default;

	bool parse(SDL_Event & event) override;
	void execute() override;
};




