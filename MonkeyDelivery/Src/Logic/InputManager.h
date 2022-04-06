#pragma once

#include "SDL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Control/CommandFactory.h"



const int FRAME_RATE = 150;
class Game;

class InputManager {
private:

	Game* game;
	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	Timer* timer_;
	
	
public:
	InputManager(Game* _game);
	~InputManager();
	void run();
	vector<SDL_Event>& GetFrameEvents(); //Vector de eventos, registra mas de 1 por frame
	void clearBackground();
	unsigned int frameDuration();
};



