#include "MissionSelectionState.h"
#include "../SelectMissionCommand.h"
#include "../PauseCommand.h"


MissionSelectionState::MissionSelectionState(Game* game) : State(game)
{
	background_ = game->getTexture(mission_UI_Panel);
	
	registerCommands();

	//// Aquí se cargan todas las texturas de todas las misiones 
	//allTextures_.push_back(game->getTexture(mission1Texture));
	//allTextures_.push_back(game->getTexture(mission2Texture));
	
}

// Constructora cuando cambiemos las texturas
MissionSelectionState::MissionSelectionState(Game* game, vector<pair<string,string>> missionImg) :  State(game)
{
	background_ = game->getTexture(mission_UI_Panel);

	// Bucle for que cargue solo las imagenes que se indican en missionImg
	for (auto a : missionImg) {
		currentTextures_.push_back(new Texture(game->getRenderer(), a.second));
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
		a = nullptr;
	}
	for (auto b : currentTextures_) {
		b = nullptr;
	}
	box_ = nullptr;
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
