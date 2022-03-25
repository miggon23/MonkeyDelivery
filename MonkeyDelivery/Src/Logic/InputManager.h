#pragma once

#include "SDL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Control/CommandFactory.h"
class Game;

class InputManager {
private:
	int joystickDeadZone_;
	SDL_Joystick* gamepad_ = NULL;

	Game* game;
	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;
	CommandFactory* commandFactory;
	SDL_Event event;
	Timer* timer_;
public:
	InputManager(Game* _game);
	~InputManager();
	void initSDL();
};



