#include "CreditsState.h"
#include "../CommandClick.h"
#include "../../Control/UI/Buttons/Back1.h"

CreditsState::CreditsState(Game* game) : State(game)
{
	
	addButton(new Back1((int)game->getWindowWidth() / 2 - buttonW/2, (int)game->getWindowHeight() - 250, buttonW, buttonH, game));
	backgroundTexture = game->getTexture(bckg_options);
	registerCommands();
	
}


void CreditsState::draw()
{
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
	backgroundTexture->render(rectPanel);
	for (auto b : getButtonsUI()) {
		b->draw();
	}

	game->renderText( "CREDITS", sdlutils().width()/2 - 100, 20);

	for (int i = 0; i < index_; i++)
	{
		game->renderText(credits_[i], sdlutils().width()/2 - 100, 100  *i);
		
	}
	
}

void CreditsState::update()
{
	if (index_ == credits_.size()) return;

	if (SDL_GetTicks() > timeNewName_ + lastName_)
	{
		index_++;
		lastName_ = SDL_GetTicks();
	}
}

void CreditsState::next()
{
}

void CreditsState::onExitState()
{
	
}

void CreditsState::onEnterState()
{
	sdlutils().musics().at("creditsmusic").play(-1);
}

void CreditsState::registerCommands()
{
	commandFactory->add(new CommandClick());
}
