#include "Button.h"

Button::Button(Game* game, int wight, int height, int x, int y) :GameObject(game) {

	setDimension(wight, height);
	setPosition(x, y);

}

void Button::update()
{
	SDL_GetMouseState(&x_, &y_);
	SDL_Rect r1 = this->getCollider();
	SDL_Rect mouse = { x_, y_, 20, 20 };

	if (SDL_HasIntersection(&r1, &mouse))
	{
		onCursorCollision();
	}
}
