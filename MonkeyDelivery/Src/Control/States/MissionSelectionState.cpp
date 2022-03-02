#include "MissionSelectionState.h"
#include "../SelectMissionCommand.h"

MissionSelectionState::MissionSelectionState(Game* game) : State(game)
{
	background_ = game->getTexture(woodPanelTexture);
	paper_ = game->getTexture(mission1);
	registerCommands();
}

MissionSelectionState::~MissionSelectionState()
{
}



void MissionSelectionState::draw()
{
	SDL_Rect textureBox = { 0, 0, game->getWindowWidth(), game->getWindowHeight()};
	background_->render(textureBox);
	
	SDL_Rect textureBox2 = { 150, 15, 500, 375};
	paper_->render(textureBox2);
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
