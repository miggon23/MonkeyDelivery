#include "DialogueBox.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../json/JSON.h"


DialogueBox::DialogueBox(Game* game) : GameObject(game)
{
	this->game = game;

	currentIcon_ = nullptr;

	font_ = new Font("../Images/TheMoon.ttf", 40);
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
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();

					text_ = vObj["text"]->AsString();

					//reinicio del texto
					reiniciateText();

					if (vObj["icon"] != NULL)
					{
						int iconId = vObj["icon"]->AsNumber();
						//cambio a la nueva textura de icono
						getIcon(iconId);
					}
					
					
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
	if (lastUpdate_ + showLetterTime_ > SDL_GetTicks())
		return;

	lastUpdate_ = SDL_GetTicks();
	
	advanceLetter();
}

void DialogueBox::advanceLetter()
{
	//si la linea a alcanzado su limite
	if (lineIndex_ >= letterPerLine_ && textLines_[currentLine_][textLines_[currentLine_].size() - 1] == 32)
	{
		string s = "";
		textLines_.push_back(s);

		if (currentLine_ != maxLines_)
		{
			currentLine_++;			
		}
		else
		{
			textLines_.erase(textLines_.begin());
		}

		//añadimos una nueva linea		
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

void DialogueBox::reiniciateText()
{
	//reinicio de la cadena con linea inicial
	textLines_.clear();
	string s = "";
	s += text_[0];
	textLines_.push_back(s);
	lineIndex_ = letterIndex_ = 1;
	currentLine_ = 0;
	showLetterTime_ = normalUpdateTime_;

	//ajuste de valores iniciales
	inShow_ = true;
	draw_ = true;
}

void DialogueBox::getIcon(unsigned int iconId)
{
	switch (iconId)
	{
	case 0:
		currentIcon_ = nullptr;
		break;
	case 1:
		currentIcon_ = game->getTexture(capibaraTexture);
		break;
	default:
		currentIcon_ = nullptr;
		break;
	}
}

void DialogueBox::interact()
{
	if (inShow_)
		showLetterTime_ = fastUpdateTime_;
	else hide();
}

void DialogueBox::draw()
{
	if (inShow_) inShow();

	if (draw_)
	{
		GameObject::draw();

		if(currentIcon_ != nullptr)
			currentIcon_->render({getX() + xIcon, getY() + yIcon, wIcon, hIcon});

		for (int i = 0; i < textLines_.size(); i++)
		{
			font_->render(game->getRenderer(), textLines_[i].c_str(), getX() + textPos_.getX(), getY() + textPos_.getY() + sizeBtwLines_ * i, color_);
		}
		
	}
}
