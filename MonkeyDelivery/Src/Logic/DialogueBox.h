#pragma once

#include <string>
#include "../View/TextureContainer.h"
#include "../View/Texture.h"
#include "../Utils/Vector2D.h"
#include "../View/Box.h"
#include "../View/Font.h"
#include "../Logic/GameObject.h"

class Game;

class DialogueBox : public GameObject
{
private:
	Font* font_;
	string text_;
	Point2D<int> textPos_;
	SDL_Color color_;

	bool draw_ = false;
public:

	
	DialogueBox(Game* game, Texture* backgroundTexture, Font* font, Point2D<double> pos, Point2D<double> size, Point2D<int> textPos, string text, SDL_Color color);
	~DialogueBox();


	void Show() { draw_ = true; }
	void Hide() { draw_ = false; }

	void draw() override;


};