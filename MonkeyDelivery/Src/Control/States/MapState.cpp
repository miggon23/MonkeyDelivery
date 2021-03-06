#include "MapState.h"
#include "../MapCommand.h"
#include "../CommandExit.h"
#include "../../sdlutils/InputHandler.h"
#include "../../Logic/MapPoint.h"

MapState::MapState(Game* game) : State(game)
{
	registerCommands();
	string path = "Images/map/minimapOverlay.png";
	backgroundTex_ = new Texture(game->getRenderer(), path);
	leyendaTex_ = game->getTexture(leyendaMapa);
	if (game->getMissionsPanel()->getCurrentMission() != nullptr)
		missionTex_ = new Texture(game->getRenderer(), "Images/missions/" + game->getMissionsPanel()->getMissionPaper() + ".png");
}

MapState::~MapState()
{
	delete backgroundTex_;  backgroundTex_ = nullptr;
	delete missionTex_;  missionTex_ = nullptr;
}

void MapState::draw()
{
	//Mapa
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth()-CUT_OFF, (int)game->getWindowHeight() };
	backgroundTex_->render(rectPanel);
	rectPanel = { (int)game->getWindowWidth() - CUT_OFF,0,(int)CUT_OFF, (int)game->getWindowHeight() };
	leyendaTex_->render(rectPanel);
	if (missionTex_ != nullptr)
	{
		rectPanel = { (int)game->getWindowWidth() - CUT_OFF + 20, (int)game->getWindowHeight() / 2, (int)CUT_OFF - 20, (int)game->getWindowHeight()/2 };
		missionTex_->render(rectPanel);
	}

	//Baliza
	game->MapPoint()->setDimension(24, 24);
	game->MapPoint()->setPosition(game->minimapinfo_.X, game->minimapinfo_.Y);

	//Evento para colocar la baliza del mapa
	auto& ihdlr = ih();
	if (ihdlr.mouseButtonEvent()) {
		
		if (ihdlr.getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)==1) {

			SDL_GetMouseState(&x_, &y_);
			if (x_ < (int)game->getWindowWidth() - CUT_OFF)
			{
				game->setPointerMapPut(true);
				game->MapPoint()->setPosition((double)x_ - 12, (double)y_ - 12);//actualizo la pos
				game->minimapinfo_.X = (double)x_ - 12;
				game->minimapinfo_.Y = (double)y_ - 12;
			}
		}
	}

	if (game->IsPointerMapPut()) {//si esta puesto el punto lo pinto
		game->MapPoint()->draw();
	}

	//Player
	int dimension = 50;
	int offset = dimension / 2;

	game->playerIcon()->setDimension(dimension, dimension);

	double x = game->getPlayer()->getX() * ((game->getWindowWidth()-CUT_OFF) / game->minimapinfo_.realW) - offset;
	double y = game->getPlayer()->getY() * (game->getWindowHeight() / game->minimapinfo_.realH) - offset;
	
	game->playerIcon()->setPosition(x, y);
	game->playerIcon()->draw();
}

void MapState::registerCommands()
{
	commandFactory->add(new MapCommand());
	commandFactory->add(new CommandExit());
}