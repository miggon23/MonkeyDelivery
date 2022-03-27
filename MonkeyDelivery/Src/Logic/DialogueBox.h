#pragma once

#include <string>
#include <vector>
#include "../View/TextureContainer.h"
#include "../View/Texture.h"
#include "../utils/Vector2D.h"
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
	Texture* currentIcon_;

	const int xPos_ = 800,
		yPos_ = 700,
		width_ = 400,
		height_ = 200,
		xText_ = 15,
		yText_ = 20,
		letterPerLine_ = 23,
		sizeBtwLines_ = 40,
		normalUpdateTime_ = 50,
		fastUpdateTime_ = 5,
		maxLines_ = 2;

	bool draw_, inShow_;

	int lastUpdate_, letterIndex_, lineIndex_, currentLine_, showLetterTime_;

	vector<string> textLines_;

public:

	//textura nombre, texto por id json
	DialogueBox(Game* game);
	~DialogueBox();
	
	void changeText(string id, Texture* newT = nullptr);
	void inShow();

	void interact();

	void advanceLetter();

	void show() { draw_ = true; inShow_ = true; }
	void hide() { draw_ = false; }
	

	void draw() override;
	void update() override {};

};