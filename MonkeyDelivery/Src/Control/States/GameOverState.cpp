#include "GameOverState.h"
#include "../../Logic/Player.h"

GameOverState::GameOverState(Game* game) : State(game)
{
	registerCommands();
}

void GameOverState::update()
{
}

void GameOverState::draw()
{
	game->renderText("GAME OVER", game->getWindowWidth() / 2 - 100, game->getWindowHeight() / 2);
	//game->DrawBrightness();
}

void GameOverState::registerCommands()
{
	commandFactory->add(new CommandExit());
}

void GameOverState::next()
{
}
