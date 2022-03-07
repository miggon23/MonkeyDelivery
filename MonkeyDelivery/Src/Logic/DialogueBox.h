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

	const int xPos_ = 300,
		yPos_ = 250, 
		width_ = 200, 
		height_ = 100, 
		xText_ = 0, 
		yText_ = 0;

	bool draw_;
public:

	//textura nombre, texto por id json
	DialogueBox(Game* game);
	~DialogueBox();
	
	void changeText(string id);
	void show() { draw_ = true; }
	void hide() { draw_ = false; }
	

	void draw() override;
	void update() override {};

};