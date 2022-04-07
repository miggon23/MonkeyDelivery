#include "CommandMove.h"
#include "../sdlutils/InputHandler.h"

bool CommandMove::parse(SDL_Event& event)
{
	auto& ihdlr = ih();
	//sin mando
	if (!ihdlr.bJoysticksInitialised()) {
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
	}
	//con mando
	else
	{
		if (ihdlr.xvalue(0, 0) == -1)
			game->setPlayerDirX(-1);
		else if (ihdlr.xvalue(0, 0) == 1)
			game->setPlayerDirX(1);
		else game->setPlayerDirX(0);

		if (ihdlr.yvalue(0, 0) == -1)
			game->setPlayerDirY(-1);
		else if (ihdlr.yvalue(0, 0) == 1)
			game->setPlayerDirY(1);
		else game->setPlayerDirY(0);



	}

	return false;
}

void CommandMove::execute()
{
	//game->move(pair<double, double>(dir, dirV)); //Movimiento del player
}