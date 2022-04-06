#pragma once
#include "Command.h"

class InventoryCommand : public Command
{
private:
	int id;
	bool use;
public:
	InventoryCommand() : id(-1),use(false) {};
	~InventoryCommand() = default;

	bool parse(SDL_Event & event) override;
	void execute() override;
};

