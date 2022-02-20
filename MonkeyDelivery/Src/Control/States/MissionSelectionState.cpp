#include "MissionSelectionState.h"

MissionSelectionState::MissionSelectionState(Game* game) : PauseState(game)
{
	background_ = game->getTexture(missionPanel);
}

MissionSelectionState::~MissionSelectionState()
{
	delete background_;
}

void MissionSelectionState::draw()
{
	SDL_Rect textureBox = { 0, 0, game->getWindowWidth(), game->getWindowHeight()};
	background_->render(textureBox);
}
