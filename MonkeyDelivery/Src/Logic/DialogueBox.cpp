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

					//reinicio de la cadena con linea inicial
					textLines_.clear();
					string s = "";
					s += text_[0];
					textLines_.push_back(s);
					lineIndex_ = letterIndex_ = 1;
					currentLine_ = 0;

					inShow_ = true;
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
	//actualizacion por tiempo
	if (lastUpdate_ + updateTime_ > SDL_GetTicks())
		return;

	lastUpdate_ = SDL_GetTicks();
	
	advanceLetter();
}

void DialogueBox::advanceLetter()
{
	//si la linea a alcanzado su limite
	if (lineIndex_ >= letterPerLine_ && textLines_[currentLine_][textLines_[currentLine_].size() - 1] == 32)
	{
		//añadimos una nueva linea
		string s = "";
		textLines_.push_back(s);
		currentLine_++;
		lineIndex_ = 0;
	}

	//suma a la linea actual la nueva letra
	textLines_[currentLine_] += text_[letterIndex_];
	//aumento del indice general y el de la linea
	letterIndex_++;
	lineIndex_++;

	//si ya no hay mas letras se acaba
	if (letterIndex_ == text_.size())
		inShow_ = false;
}

void DialogueBox::fastShow()
{
	if (!inShow_) return;

	while (!inShow_) advanceLetter();
}

void DialogueBox::draw()
{
	if (inShow_) inShow();

	if (draw_)
	{
		GameObject::draw();
		for (int i = 0; i < textLines_.size(); i++)
		{
			font_->render(game->getRenderer(), textLines_[i].c_str(), getX() + textPos_.getX(), getY() + textPos_.getY() + sizeBtwLines * i, color_);
		}
		
	}
}
