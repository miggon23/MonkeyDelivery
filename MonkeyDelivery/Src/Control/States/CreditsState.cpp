#include "CreditsState.h"
#include "../CommandClick.h"
#include "../SelectButtonCommand.h"
#include "../../Control/UI/Buttons/Back1.h"
#include "../../json/JSON.h"


CreditsState::CreditsState(Game* game) : State(game)
{
	buttonW = (int)game->getWindowWidth() / 6;
	buttonH = (int)(game->getWindowHeight() / 7.143);

	addButton(new Back1((int)game->getWindowWidth() / 2 - buttonW/2, (int)game->getWindowHeight() - 250, buttonW, buttonH, game));
	backgroundTexture = game->getTexture(bckg_options);
	selectorTexture = game->getTexture(mission_UI_Selector);

	loadCredits("Images/config/resources.json");

	registerCommands();
}

void CreditsState::draw()
{
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
	backgroundTexture->render(rectPanel);
	for (auto b : getButtonsUI()) {
		b->draw();
	}

	game->renderText( "CREDITS", sdlutils().width()/2 + 100, 20);

	for (int i = 0; i < index_; i++)
	{
		game->renderText(credits_[i], sdlutils().width()/2 + 350, 100  *(i+1));
	}

	rectPanel = { (int)buttonsUI[0]->getPosition().getX(), (int)buttonsUI[0]->getPosition().getY(), (int)buttonsUI[0]->getWidth(), (int)buttonsUI[0]->getHeight() };
	selectorTexture->render(rectPanel);
	
}

void CreditsState::update()
{
	if (index_ == credits_.size()) return;

	if ((int)SDL_GetTicks() > timeNewName_ + lastName_)
	{
		index_++;
		lastName_ = SDL_GetTicks();
	}
}

void CreditsState::loadCredits(std::string filename)
{
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;
	

	jValue = root["credits"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					
					JSONObject vObj = v->AsObject();
					std::string key = vObj["name"]->AsString();
					credits_.push_back(key);
				}
			}
		}
	}
}

void CreditsState::onEnterState()
{
	sdlutils().musics().at("creditsmusic").play(-1);
}

void CreditsState::registerCommands()
{
	commandFactory->add(new CommandClick());
	commandFactory->add(new SelectButtonCommand(this));
}