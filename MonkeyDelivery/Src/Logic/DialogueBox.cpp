#include "DialogueBox.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../json/JSON.h"


DialogueBox::DialogueBox(Game* game) : GameObject(game)
{
	this->game = game;


	font_ = new Font("../Images/TheMoon.ttf", 20);
	texture = game->getTexture(dialogoPrueba);
	color_ = BLACK;

	setPosition(xPos_, yPos_);
	setDimension(width_, height_);
	textPos_ = { xText_, yText_ };
}

DialogueBox::~DialogueBox()
{	
	delete font_;
	font_ = nullptr;
}

void DialogueBox::changeText(string id)
{
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile("../Images/config/resources.json"));


	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '../Images/config/resources.json'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	jValue = root[id];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			int x, y, width, height, xText, yText;
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();

					text_ = vObj["text"]->AsString();
					//reinicio de la cadena
					currentText_ = text_[0];
				}
				else {
					throw "'missions' array in '" + id
						+ "' includes and invalid value";
				}
			}

			
		}
		else {
			throw "'fonts' is not an array in '" + id + "'";
		}
	}
}

void DialogueBox::inShow()
{
	if (lastUpdate_ + updateTime_ > SDL_GetTicks())
		return;

	lastUpdate_ = SDL_GetTicks();

	currentText_ += text_[letterIndex_];
	letterIndex_++;

	if (currentText_.size() == text_.size())
		inShow_ = false;
}

void DialogueBox::draw()
{
	if (inShow_) inShow();

	if (draw_)
	{
		GameObject::draw();
		font_->render(game->getRenderer(), currentText_.c_str(), getX() + textPos_.getX(), getY() + textPos_.getY(), color_);
	}
}
