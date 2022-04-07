#pragma once
#include "Command.h"

class CommandRun :public Command {

	bool isRunning = false;		//Variable que indica si el player corre
public:
	CommandRun() {};
	~CommandRun() = default;

	bool parse(SDL_Event& event) override;
	void execute() override;
};