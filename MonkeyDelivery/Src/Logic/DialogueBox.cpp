#include "DialogueBox.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../json/JSON.h"


DialogueBox::DialogueBox(Game* game) : GameObject(game)
{
	this->game = game;

	currentIcon_ = nullptr;

	font_ = new Font("Images/fonts/Pixellari.ttf", 40);
	texture = game->getTexture(UI_dialogueBox);
	color_ = BLACK;


	
	yPos_ = (int)(game->getWindowHeight()/1.43);
	width_ = (int)(game->getWindowWidth()/7.5 * 2);
	xPos_ = (int)(game->getWindowWidth() / 2 - width_ / 2);
	height_ = (int)(game->getWindowHeight()/11.37 * 2);
	xText_ = (int)(game->getWindowWidth()/120.0);
	yText_ = (int)(game->getWindowHeight()/50.0);
	xIcon = (int)(- game->getWindowWidth()/36.0);
	yIcon = (int)(-game->getWindowHeight()/17.24);
	wIcon = (int)(game->getWindowWidth()/14.4);
	hIcon = (int)(game->getWindowHeight()/8.0);
	
	

	setPosition(xPos_, yPos_);
	setDimension(width_, height_);
	textPos_ = { xText_, yText_ };

	loadTexts();
}

DialogueBox::~DialogueBox()
{	
	delete font_;
	font_ = nullptr;
}

void DialogueBox::changeText(string id)
{
	// cambiar texto
	text_ = textList_.at(id);

	//reinicio del texto
	reiniciateText();

	// cambiar icono
	double iconId = -1;
	//cambio a la nueva textura de icono
	getIcon(iconId);
}

void DialogueBox::changeMissionText(string id) {
	isMissionText = true;
	changeText(id);
}
void DialogueBox::inShow()
{
	//actualizacion por tiempo
	if (lastUpdate_ + showLetterTime_ > (int)SDL_GetTicks())
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
	if (letterIndex_ == text_.size()){
		inShow_ = false;
	}

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
	case 1:
		currentIcon_ = game->getTexture(npc_Fox);
		break;
	default:
		currentIcon_ = nullptr;
		break;
	}
}

bool DialogueBox::interact()
{
	if (!draw_) return false;

	if (inShow_)
		showLetterTime_ = fastUpdateTime_;
	else {
		hide();
		game->dialogueEnd(isMissionText);
		isMissionText = false;
	}
	return true;
}

void DialogueBox::loadTexts()
{
	string filename = "Images/config/resources.json";
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing 'Images/config/resources.json'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	jValue = root["dialogues"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();

					std::string id = vObj["id"]->AsString();
					std::string text = vObj["text"]->AsString();

					textList_.insert(std::make_pair(id, text));

					// cargar iconos

					//if (vObj["icon"] != nullptr)
					//	iconId = vObj["icon"]->AsNumber();
				}
				else {
					throw "'missions' array in '" + filename
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'fonts' is not an array in '" + filename + "'";
		}
	}
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
