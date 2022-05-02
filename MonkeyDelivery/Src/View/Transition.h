#pragma once
#include <SDL.h>

class Game;
class Texture;
class Transition
{
private:
	Game* game;
	int size = 0;
	int increase = 30;
	Texture* maskTexture;
	bool completed = false;

public:
	Transition(Game* g);
	~Transition();
	void draw();
	void restart();
	inline bool isComplete() { return completed; };
};

