#pragma once

#include <string>
#include <vector>
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
		xText_ = 10,
		yText_ = 0,
		letterPerLine_ = 20,
		sizeBtwLines = 20,
		updateTime_ = 50;

	bool draw_, inShow_;

	int lastUpdate_, letterIndex_, lineIndex_, currentLine_;

	vector<string> textLines_;

public:

	//textura nombre, texto por id json
	DialogueBox(Game* game);
	~DialogueBox();
	
	void changeText(string id);
	void inShow();

	void fastShow();

	void advanceLetter();

	void show() { draw_ = true; inShow_ = true; }
	void hide() { draw_ = false; }
	

	void draw() override;
	void update() override {};

};