#pragma once
#include "Src/Logic/Game.h"

class MessageOverlay
{
	MessageOverlay(Game* game, AnimationManager* animation);
	~MessageOverlay() {};
	private:
		void draw();
		bool canTakeMission = true;
};

