#pragma once
#include "Command.h"

class MapCommand:public Command
{

public:
	const string INFO_STRING = "[m] to open the map";

	MapCommand();
	~MapCommand() = default;

	bool parse(SDL_Event & event) override;
	void execute() override;
};