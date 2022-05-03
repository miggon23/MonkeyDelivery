#include "MissionSelectionState.h"
#include "../SelectMissionCommand.h"
#include "../PauseCommand.h"


MissionSelectionState::MissionSelectionState(Game* game) : State(game)
{
	background_ = game->getTexture(mission_UI_Panel);
	controls_ = game->getTexture(UI_MissionsControls);
	
	registerCommands();
}

// Constructora cuando cambiemos las texturas
MissionSelectionState::MissionSelectionState(Game* game, vector<pair<string,string>> missionImg) :  State(game)
{
	background_ = game->getTexture(mission_UI_Panel);
	controls_ = game->getTexture(UI_MissionsControls);

	// Bucle for que cargue solo las imagenes que se indican en missionImg
	for (auto a : missionImg) {
		Texture* tex = nullptr;
		if (a.second == "Mission01") {
			tex = game->getTexture(Mission01);
		}else if (a.second == "Mission02") {
			tex = game->getTexture(Mission02);
		}else if (a.second == "Mission03") {
			tex = game->getTexture(Mission07);
		}else if (a.second == "Mission04") {
			tex = game->getTexture(Mission07);
		}else if (a.second == "Mission05") {
			tex = game->getTexture(Mission07);
		}else if (a.second == "Mission06") {
			tex = game->getTexture(Mission07);
		}else if (a.second == "Mission07") {
			tex = game->getTexture(Mission07);
		}else if (a.second == "Mission08") {
			tex = game->getTexture(Mission07);
		}else if (a.second == "Mission09") {
			tex = game->getTexture(Mission07);
		}
		if (tex != nullptr)
			currentTextures_.push_back(tex);

		missionData_.push_back(a.first);
	}

	offsetX_ = (int)game->getWindowWidth() / 18;
	xInc_ = (int)(game->getWindowWidth() / 3.27);
	ySize_ = (int)(game->getWindowHeight() / 6.66);
	wSize_ = (int)(game->getWindowWidth() / 3.6);
	hSize_ = (int)(game->getWindowHeight() / 1.6);
	h2Size_ = (int)(game->getWindowHeight() / 1.7);

	buttonsX_ = (int)(game->getWindowWidth()/1.3);
	buttonsY_ = (int)(game->getWindowHeight()/1.3);
	buttonsW_ = 450;
	buttonsH_ = 200;

	//currentSelection_ = missionImg[0].first; ->if it's string
	currentSelection_ = 0;

	box_ = game->getTexture(mission_UI_Selector);
	boxXPos_ = offsetX_;

	registerCommands();
}

MissionSelectionState::~MissionSelectionState()
{
	for (auto a : allTextures_) {
		delete a;
		a = nullptr;
	}
	box_ = nullptr;
	background_ = nullptr;
}

void MissionSelectionState::draw()
{
	SDL_Rect textureBox = { 0, 0, (int)game->getWindowWidth(), (int)game->getWindowHeight() };
	background_->render(textureBox);

	int x = offsetX_;
	for (auto a : currentTextures_) {
		textureBox = { x, ySize_, wSize_, hSize_ };
		a->render(textureBox);
		x += xInc_;
	}

	SDL_Rect textureBox2 = { boxXPos_, ySize_, wSize_, h2Size_ };
	box_->render(textureBox2);

	SDL_Rect textureBox3 = { buttonsX_, buttonsY_, buttonsW_, buttonsH_ };
	controls_->render(textureBox3);
	
}

void MissionSelectionState::registerCommands()
{
	commandFactory->add(new CommandExit());
	commandFactory->add(new SelectMissionCommand(this));
	commandFactory->add(new PauseCommand());
}

void MissionSelectionState::moveBox(int i)
{
	if (i == -1 && currentSelection_ != 0) {

		boxXPos_ += i * xInc_;
		currentSelection_--;
	}
	else if (i == 1 && currentSelection_ != missionData_.size() - 1) {
		boxXPos_ += i * xInc_;
		currentSelection_++;
	}
}

string MissionSelectionState::getSelectedMission()
{
	return missionData_[currentSelection_];
}
