#include "CommandMove.h"
#include "../sdlutils/InputHandler.h"
bool CommandMove::parse(SDL_Event& event)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	auto& ihdlr = ih();
	if (ihdlr.keyDownEvent()) {
		//eje x
		if (ihdlr.isKeyDown(SDL_SCANCODE_A))
			game->setPlayerDirX(-1);
		else if (ihdlr.isKeyDown(SDL_SCANCODE_D))
			game->setPlayerDirX(1);
		else game->setPlayerDirX(0);
		//eje y
		if (ihdlr.isKeyDown(SDL_SCANCODE_S))
			game->setPlayerDirY(1);
		else if (ihdlr.isKeyDown(SDL_SCANCODE_W))
			game->setPlayerDirY(-1);
		else game->setPlayerDirY(0);
	}
	return false;
}

void CommandMove::execute()
{
	//game->move(pair<double, double>(dir, dirV)); //Movimiento del player

}
