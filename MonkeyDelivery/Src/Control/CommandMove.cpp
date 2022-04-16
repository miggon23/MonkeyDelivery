#include "CommandMove.h"
#include "../sdlutils/InputHandler.h"

bool CommandMove::parse(SDL_Event& event)
{
	auto& ihdlr = ih();

	if (ihdlr.xvalue(0, 0) == -1 || ihdlr.isKeyDown(SDL_SCANCODE_A))
		game->setPlayerDirX(-1);
	else if (ihdlr.xvalue(0, 0) == 1 || ihdlr.isKeyDown(SDL_SCANCODE_D))
		game->setPlayerDirX(1);
	else game->setPlayerDirX(0);

	if (ihdlr.yvalue(0, 0) == -1 || ihdlr.isKeyDown(SDL_SCANCODE_W))
		game->setPlayerDirY(-1);
	else if (ihdlr.yvalue(0, 0) == 1 || ihdlr.isKeyDown(SDL_SCANCODE_S))
		game->setPlayerDirY(1);
	else game->setPlayerDirY(0);

	return false;
}

void CommandMove::execute()
{
	//game->move(pair<double, double>(dir, dirV)); //Movimiento del player
}