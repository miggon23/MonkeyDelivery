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

	//textura nombre, texto por id json
	DialogueBox(Game* game, string id, Font* font, SDL_Color color, Texture* texture);
	~DialogueBox();
	void Load(string filename, string id);

	void ChangeText(string text);
	void Show() { draw_ = true; }
	void Hide() { draw_ = false; }
	

	void draw() override;
	void update() override {};

};