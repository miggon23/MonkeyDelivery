#include "MapState.h"
#include "../MapCommand.h"
#include "../CommandExit.h"

MapState::MapState(Game* game) : State(game)
{
	registerCommands();
	string path = "../Images/Mapa/imagenMiniMapa.png";
	backgroundTex_ = new Texture(game->getRenderer(), path);
}

MapState::~MapState()
{
	delete backgroundTex_;
	backgroundTex_ = nullptr;
}

void MapState::update()
{
}

void MapState::draw()
{
	SDL_Rect rectPanel = { 0,0,game->getWindowWidth(),game->getWindowHeight() };
	backgroundTex_->render(rectPanel);
}

void MapState::next()
{
}

void MapState::registerCommands()
{
	commandFactory->add(new MapCommand());
	commandFactory->add(new CommandExit());
}
