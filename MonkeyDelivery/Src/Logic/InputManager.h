#pragma once

#include "SDL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Control/CommandFactory.h"


const int FRAME_RATE_ = 60;


class Game;

class InputManager {
private:
	int joystickDeadZone_;
	SDL_Joystick* gamepad_ = NULL;
	//CommandFactory* commandFactory = nullptr;

	Game* game;
	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	Timer* timer_;
	
	void initSDL();
public:
	InputManager(Game* _game);
	~InputManager();
	void run();
	void handleEvents();
	vector<SDL_Event>& GetFrameEvents(); //Vector de eventos, registra mas de 1 por frame
	void clearBackground();
	unsigned int frameDuration();
};



