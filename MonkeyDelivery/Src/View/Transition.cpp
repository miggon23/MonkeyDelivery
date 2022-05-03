#include "Transition.h"
#include "../Logic/Game.h"

Transition::Transition(Game* g) : game(g)
{
	maskTexture = game->getTexture(transitionTex);
}

Transition::~Transition()
{
	maskTexture = nullptr;
	game = nullptr;
}

void Transition::draw()
{
	if (!completed) {

	 /*2- Calculate the size of mask texture. Increment size each frame by a fitting amount.
	  You would then use this value to calculate the destination rectangle for the sprite. */
		size += increase;
		SDL_Rect dest = {(game->getWindowWidth() / 2) - (size / 2), (game->getWindowHeight() / 2) - (size / 2), size, size};

	  /*3- Before rendering your actual game objects, call SDL_RenderSetClipRect(renderer, &dest);
	  This assures that nothing is rendered outside of the(square) circle texture area. That way everything outside of the texture should stay black.*/
		SDL_RenderSetClipRect(game->getRenderer(), &dest);

	  /*4- Finally, simply render your mask texture onto the screen : SDL_RenderCopy(renderer, maskTexture, NULL, &dest);*/
		maskTexture->render(dest, SDL_FLIP_NONE);
		//SDL_RenderCopy(game->getRenderer(), maskTexture, NULL, &dest);

	  /*5- Figure out when the effect has finished. */
		if (size >= game->getWindowWidth() + 1500) { // offset para que la animacion sea más fluida
			completed = true;
		}
	}
}

void Transition::restart()
{
	completed = false;
	size = 0;
}
