#include "MissionSelectionState.h"
#include "../SelectMissionCommand.h"

MissionSelectionState::MissionSelectionState(Game* game) : State(game)
{
	background_ = game->getTexture(missionPanel);
	registerCommands();
}

MissionSelectionState::~MissionSelectionState()
{
}

void MissionSelectionState::draw()
{
	SDL_Rect textureBox = { 0, 0, game->getWindowWidth(), game->getWindowHeight()};
	background_->render(textureBox);
}

void MissionSelectionState::update()
{
}

void MissionSelectionState::next()
{
}

void MissionSelectionState::registerCommands()
{
	commandFactory->add(new CommandExit());
	commandFactory->add(new SelectMissionCommand());
}
