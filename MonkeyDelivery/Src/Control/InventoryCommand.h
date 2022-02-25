#pragma once
#include "Command.h"

class InventoryCommand : public Command
{
private:
	int id;
public:
	InventoryCommand() : id(-1) {};
	~InventoryCommand() = default;

	bool parse(SDL_Event & event) override;
	void execute() override;
};

