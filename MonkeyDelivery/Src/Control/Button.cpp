#include "Button.h"

Button::Button(Game* game, int wight, int height, int x, int y) :GameObject(game) {

	setDimension(wight, height);
	setPosition(x, y);

}

Button::Button(Game* game, int x, int y):GameObject(game){
	setDimension(100, 100);
	setPosition(x, y);
}

bool Button::onClick()
{
	SDL_GetMouseState(&x_, &y_);
	SDL_Rect r1 = this->getCollider();
	SDL_Rect mouse = { x_, y_, 20, 20 };

	if (SDL_HasIntersection(&r1, &mouse))
	{
		return true;
	}
	return false;
}

void Button::update()
{
	/*
	while ((SDL_PollEvent(event)))
	{
		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&x_, &y_);
			SDL_Rect r1 = this->getCollider();
			SDL_Rect mouse = { x_, y_, 20, 20 };

			if (SDL_HasIntersection(&r1, &mouse))
			{
				onCursorCollision();
			}
		}
	}
	SDL_GetMouseState(&x_, &y_);
	SDL_Rect r1 = this->getCollider();
	SDL_Rect mouse = { x_, y_, 20, 20 };

	if (SDL_HasIntersection(&r1, &mouse))
	{
		onCursorCollision();
	}
	SDL_GetMouseState(&x_, &y_);
	SDL_Rect r1 = this->getCollider();
	SDL_Rect mouse = { x_, y_, 20, 20 };

	if (SDL_HasIntersection(&r1, &mouse))
	{
		onCursorCollision();
	}*/
}

//
//bool Button::parse(SDL_Event& event)
//{
//	if (event.type == SDL_MOUSEBUTTONDOWN) {
//		SDL_GetMouseState(&x_, &y_);
//		SDL_Rect r1 = this->getCollider();
//		SDL_Rect mouse = { x_, y_, 20, 20 };
//
//		if (SDL_HasIntersection(&r1, &mouse))
//		{
//			onCursorCollision();
//		}		
//	}
//		
//	return false;
//}

