#pragma once
#include "Command.h"

class CommandRun :public Command {

	bool isRunning = false;
public:
	CommandRun() {};
	~CommandRun() = default;

	bool parse(SDL_Event& event) override;
	void execute() override;
};