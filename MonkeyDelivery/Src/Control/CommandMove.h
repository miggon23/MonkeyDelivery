#pragma once
#include "Command.h"

class CommandMove :public Command {

	int dir=0;
public:
	CommandMove() {};
	~CommandMove()=default;

	bool parse(SDL_Event& event) override;
	void execute() override;
};
