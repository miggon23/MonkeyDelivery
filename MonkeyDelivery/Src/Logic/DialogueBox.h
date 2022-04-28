#pragma once

#include <string>
#include <vector>
#include <map>

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

	map<string, string> textList_;

	Font* font_;
	string text_;
	Point2D<int> textPos_;
	SDL_Color color_;
	Texture* currentIcon_;

	int xPos_ = 500,
		yPos_ = 700,
		width_ = 240*2,
		height_ = 88*2,
		xText_ = 15,
		yText_ = 20,
		xIcon = -50,
		yIcon = -58,
		wIcon = 125,
		hIcon = 125,
		letterPerLine_ = 20,
		sizeBtwLines_ = 40,
		normalUpdateTime_ = 50,
		fastUpdateTime_ = 5,
		maxLines_ = 2;

	bool draw_, inShow_;

	int lastUpdate_, letterIndex_, lineIndex_, currentLine_, showLetterTime_;

	vector<string> textLines_;

	bool isMissionText = false;
public:

	//textura nombre, texto por id json
	DialogueBox(Game* game);
	~DialogueBox();
	
	void loadTexts();

	void changeText(string id);
	void changeMissionText(string id); // los textos de mision tienen una función distinta al acabar
	void inShow();

	bool interact();

	void advanceLetter();

	void reiniciateText();

	void getIcon(unsigned int iconId);

	void show() { draw_ = true; inShow_ = true; }
	void hide() { draw_ = false; }
	

	void draw() override;
	void update() override {};

};