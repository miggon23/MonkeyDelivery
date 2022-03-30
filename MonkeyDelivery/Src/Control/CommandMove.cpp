#include "CommandMove.h"
#include "../sdlutils/InputHandler.h"
bool CommandMove::parse(SDL_Event& event)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	auto& ihdlr = ih();
	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(SDL_SCANCODE_X))
			cout << "SOCORRO";
	}
	if (state[SDL_SCANCODE_A]) {
		//dir = -1;
		game->setPlayerDirX(-1);
		//game->move(pair<double, double>(dir, 0));
	}
	else if (state[SDL_SCANCODE_D]) {
		//dir = 1;
		game->setPlayerDirX(1);
		//game->move(pair<double, double>(dir, 0));
	}
	else game->setPlayerDirX(0);
	if (state[SDL_SCANCODE_S]) {
		/*dirV = 1;
		game->move(pair<double, double>(0, dirV));*/
		game->setPlayerDirY(1);
	}
	else if (state[SDL_SCANCODE_W]) {
		/*dirV = -1;
		game->move(pair<double, double>(0, dirV));*/
		game->setPlayerDirY(-1);
	}
	else game->setPlayerDirY(0);
	return false;
}

void CommandMove::execute()
{
	//game->move(pair<double, double>(dir, dirV)); //Movimiento del player
	
}
