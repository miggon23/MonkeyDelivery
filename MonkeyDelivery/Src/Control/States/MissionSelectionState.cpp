#include "MissionSelectionState.h"
#include "../SelectMissionCommand.h"


MissionSelectionState::MissionSelectionState(Game* game) : State(game)
{
	background_ = game->getTexture(woodPanelTexture);
	
	registerCommands();

	//// Aquí se cargan todas las texturas de todas las misiones 
	//allTextures_.push_back(game->getTexture(mission1Texture));
	//allTextures_.push_back(game->getTexture(mission2Texture));
	
}

// Constructora cuando cambiemos las texturas
MissionSelectionState::MissionSelectionState(Game* game, vector<pair<string,string>> missionImg) :  State(game)
{
	background_ = game->getTexture(woodPanelTexture);	

	// Bucle for que cargue solo las imagenes que se indican en missionImg
	for (auto a : missionImg) {
		currentTextures_.push_back(new Texture(game->getRenderer(), a.second));
		missionData_.push_back(a.first);
	}

	//currentSelection_ = missionImg[0].first; ->if it's string
	currentSelection_ = 0;

	box_ = new Texture(game->getRenderer(), "../Images/shop/seleccion.png");
	boxXPos_ = 100;

	registerCommands();
}

MissionSelectionState::~MissionSelectionState()
{
	for (auto a : allTextures_) {
		delete a;
	}
	for (auto b : currentTextures_) {
		delete b;
	}
	delete box_;
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

	SDL_Rect textureBox = { 0, 0, game->getWindowWidth(), game->getWindowHeight() };
	background_->render(textureBox);

	int x = 100;
	for (auto a : currentTextures_) {
		textureBox = { x, 50, 550, 475 };
		a->render(textureBox);
		x += xInc_;
	}

	SDL_Rect textureBox2 = { boxXPos_, 50, 550, 475 };
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
