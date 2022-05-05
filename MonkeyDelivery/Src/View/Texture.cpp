#include "Texture.h"
#include <iostream>

using namespace std;

void Texture::free() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

void Texture::load(string filename, uint numRows, uint numCols) {

	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr)
		throw string("Error loading surface: " + filename);
	free();

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw string("Error loading texture: " + filename);

	//cout << "[DEBUG] Loading texture... " << filename << endl;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

void Texture::render(const SDL_Rect& rect, double angle, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &rect, angle, 0, flip);
}
