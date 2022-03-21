#include "CreditsState.h"
#include "../CommandClick.h"

CreditsState::CreditsState(Game* game, Font* font) : State(game), font_(font)
{

	registerCommands();
}


void CreditsState::draw()
{
	for (auto b : getButtonsUI()) {
		b->draw();
	}

	font_->render(game->getRenderer(), "CREDITS", 100, 20, BLACK);

	for (int i = 0; i < index_; i++)
	{
		font_->render(game->getRenderer(), credits_[i], 100, 20, BLACK);
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

void CreditsState::registerCommands()
{
	commandFactory->add(new CommandClick());
}
