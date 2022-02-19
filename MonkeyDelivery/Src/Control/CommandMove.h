#pragma once
#include "Command.h"

class CommandMove :public Command {

	int dir=0, dirV=0;			//Varibles de la direccion del movimiento
	bool isRunning = false;		//Variable que indica si el player corre
public:
	CommandMove() {};
	~CommandMove()=default;

	bool parse(SDL_Event& event) override;
	void execute() override;
};
