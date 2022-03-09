#include "GameOverState.h"

GameOverState::GameOverState(Game* game, ViewController *v) : State(game, v)
{
	registerCommands();
}

void GameOverState::update()
{
}

void GameOverState::draw()
{
}

void GameOverState::registerCommands()
{
}
