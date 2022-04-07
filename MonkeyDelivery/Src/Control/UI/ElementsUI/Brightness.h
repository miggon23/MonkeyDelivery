#pragma once
#include <SDL.h>
#include "../../../View/Texture.h"

using namespace std;
typedef unsigned int uint;


class Game;
class Brightness {
	Game* game_;
	Texture* tex_;
	SDL_Rect rect_ = {0,0,1920,1080};
	Uint8 alpha_;
public:
	Brightness(Game* game);
	~Brightness();
	void draw();
	void changeAlhpa(Uint8 newAlpha);
};