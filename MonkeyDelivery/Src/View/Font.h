#pragma once

#include "SDL.h"
#include "SDL_ttf.h" 
#include <string>
#include <iostream>

using namespace std;

class Font {
private:
	TTF_Font* font = nullptr;
	int size;
public:
	Font(string filename, int _size) {
		size = _size;
		load(filename, size);

	}
	~Font() {
		free();
	}

	int getSize() {
		return size;
	}

	bool load(string filename, int size) {
		TTF_Init();
		font = TTF_OpenFont(filename.c_str(), size);

		if (font == nullptr)
			throw string("Error loading font " + filename);

		cout << "[DEBUG] Loading font " << filename << endl;
		return true;
	}
	void free() {
		if (font != nullptr)
			TTF_CloseFont(font);
		font = nullptr;
		TTF_Quit();
	}

	void render(SDL_Renderer* renderer, string text, int x, int y, SDL_Color color) {
		SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect rect = SDL_Rect{ x, y, textSurface->w, textSurface->h };
		SDL_RenderCopy(renderer, textTexture, NULL, &rect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
};


