#include "GameOverState.h"
#include "../../Player/Player.h"

GameOverState::GameOverState(Game* game) : State(game)
{
	registerCommands();
}

void GameOverState::draw()
{
	game->renderText("GAME OVER", (int)game->getWindowWidth() / 2 - 100, (int)game->getWindowHeight() / 2);
}

void GameOverState::registerCommands()
{
	commandFactory->add(new CommandExit());
}