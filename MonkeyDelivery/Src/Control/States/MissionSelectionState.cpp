#include "MissionSelectionState.h"
#include "../SelectMissionCommand.h"


MissionSelectionState::MissionSelectionState(Game* game) : State(game)
{
	background_ = game->getTexture(woodPanelTexture);
	
	registerCommands();

	// Aquí se cargan todas las texturas de todas las misiones 
	allTextures_.push_back(game->getTexture(mission1Texture));
	allTextures_.push_back(game->getTexture(mission2Texture));
	
}

// Constructora cuando cambiemos las texturas
MissionSelectionState::MissionSelectionState(Game* game, vector<string> missionImg) :  State(game)
{
	background_ = game->getTexture(woodPanelTexture);	

	// Bucle for que cargue solo las imagenes que se indican en missionImg
	for (auto a : missionImg) {
		currentTextures_.push_back(new Texture(game->getRenderer(), a));
	}

	registerCommands();
}

MissionSelectionState::~MissionSelectionState()
{
	for (auto a : allTextures_) {
		delete a;
	}
	for (auto a : currentTextures_) {
		delete a;
	}
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
		SDL_Rect textureBox = { x, 50, 350, 275 };
		a->render(textureBox);
		x += 310;
	}

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
