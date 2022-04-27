#include "MissionSelectionState.h"
#include "../SelectMissionCommand.h"
#include "../PauseCommand.h"


MissionSelectionState::MissionSelectionState(Game* game) : State(game)
{
	background_ = game->getTexture(mission_UI_Panel);
	controls_ = game->getTexture(UI_MissionsControls);
	
	registerCommands();

	//// Aquí se cargan todas las texturas de todas las misiones 
	//allTextures_.push_back(game->getTexture(Mission01));
	//allTextures_.push_back(game->getTexture(Mission02));
	//allTextures_.push_back(game->getTexture(Mission07));
	
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

	//currentSelection_ = missionImg[0].first; ->if it's string
	currentSelection_ = 0;

	box_ = game->getTexture(mission_UI_Selector);
	boxXPos_ = 100;

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
	/*SDL_Rect textureBox = { 0, 0, game->getWindowWidth(), game->getWindowHeight()};
	background_->render(textureBox);
	
	SDL_Rect textureBox2 = { 150, 15, 500, 375};
	paper_->render(textureBox2);*/

	/*for (auto c : missionImages_) {
		SDL_Rect textureBox2 = { 150, 15, 500, 375 };
		paper_->render(textureBox2);
	}*/

	SDL_Rect textureBox = { 0, 0, (int)game->getWindowWidth(), (int)game->getWindowHeight() };
	background_->render(textureBox);

	int x = 100;
	for (auto a : currentTextures_) {
		textureBox = { x, 150, 500, 640 };
		a->render(textureBox);
		x += xInc_;
	}

	SDL_Rect textureBox2 = { boxXPos_, 150, 500, 614 };
	box_->render(textureBox2);

	double xPosRatio = game->getWindowWidth() / 1380.0;
	double yPosRatio = game->getWindowHeight() / 770.0;
	double xRatio = game->getWindowWidth() / 300.0;
	double yRatio = game->getWindowHeight() / 170.0;

	SDL_Rect textureBox3 = { game->getWindowWidth()/xPosRatio, game->getWindowHeight()/yPosRatio, game->getWindowWidth() / xRatio, game->getWindowHeight() / yRatio };
	controls_->render(textureBox3);
	
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
