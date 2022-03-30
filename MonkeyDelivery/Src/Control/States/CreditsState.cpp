#include "CreditsState.h"
#include "../CommandClick.h"
#include "../../Control/UI/Buttons/Back.h"

CreditsState::CreditsState(Game* game) : State(game)
{
	
	addButton(new Back(game->getWindowWidth() / 2 - 50, game->getWindowHeight() - 250, 100, 75, game));
	registerCommands();
}


void CreditsState::draw()
{
	for (auto b : getButtonsUI()) {
		b->draw();
	}

	game->renderText( "CREDITS", sdlutils().width()/2 - 100, 20);

	for (int i = 0; i < index_; i++)
	{
		game->renderText(credits_[i], sdlutils().width()/2 - 100, 100  *i);
		
	}
	game->DrawBrightness();
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

void CreditsState::registerCommands()
{
	commandFactory->add(new CommandClick());
}
