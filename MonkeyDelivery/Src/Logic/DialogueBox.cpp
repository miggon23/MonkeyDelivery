#include "DialogueBox.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../json/JSON.h"


DialogueBox::DialogueBox(Game* game, string id, Font* font, SDL_Color color, Texture* texture) : GameObject(game)
{
	this->game = game;
	this->texture = texture;
	
	Load("../Images/config/resources.json", id);

	font_ = font;	
	color_ = color;


}

DialogueBox::~DialogueBox()
{	
	delete font_;
	font_ = nullptr;
}

void DialogueBox::Load(string filename, string id)
{
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
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
					x = vObj["x"]->AsNumber();
					y = vObj["y"]->AsNumber();
					width = vObj["width"]->AsNumber();
					height = vObj["height"]->AsNumber();
					xText = vObj["xText"]->AsNumber();
					yText = vObj["yText"]->AsNumber();
				}
				else {
					throw "'missions' array in '" + filename
						+ "' includes and invalid value";
				}
			}

			setPosition(x, y);
			setDimension(width, height);
			textPos_ = { xText, yText };
		}
		else {
			throw "'fonts' is not an array in '" + filename + "'";
		}
	}
}

void DialogueBox::ChangeText(string text)
{
	text_ = text;
}

void DialogueBox::draw()
{
	if (draw_)
	{
		GameObject::draw();
		font_->render(game->getRenderer(), text_.c_str(), getX() + textPos_.getX(), getY() + textPos_.getY(), color_);
	}
}
