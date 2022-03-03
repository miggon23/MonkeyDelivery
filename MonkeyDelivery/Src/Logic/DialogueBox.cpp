#include "DialogueBox.h"
#include "Game.h"



DialogueBox::DialogueBox(Game* game, Texture* backgroundTexture, Font* font, Point2D<double> pos, Point2D<double> size, Point2D<int> textPos, string text, SDL_Color color) : GameObject(game)
{
	this->game = game;
	this->texture = backgroundTexture;
	setPosition(pos.getX(), pos.getY());
	setDimension(size.getX(), size.getY());
	textPos_ = textPos;
	font_ = font;
	text_ = text;
	color_ = color;
}

DialogueBox::~DialogueBox()
{	
	font_ = nullptr;
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
