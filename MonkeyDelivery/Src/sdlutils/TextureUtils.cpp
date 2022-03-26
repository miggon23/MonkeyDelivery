// This file is part of the course TPV2@UCM - Samir Genaim

#include "TextureUtils.h"

TextureUtils& TextureUtils::operator=(TextureUtils&&other) noexcept {
	this->~TextureUtils();
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;

	return *this;
}

TextureUtils::TextureUtils(TextureUtils&&other) noexcept {
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;
}

TextureUtils::TextureUtils(SDL_Renderer *renderer, const std::string &fileName) {
	assert(renderer != nullptr);

	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(surface);
		throw "Couldn't load image: " + fileName;
	}

	width_ = surface->w;
	height_ = surface->h;
	renderer_ = renderer;

}

TextureUtils::TextureUtils(SDL_Renderer *renderer, const std::string &text,
		const FontUtils&font, const SDL_Color &fgColor) {
	constructFromText(renderer, text, font, &fgColor);
}

TextureUtils::TextureUtils(SDL_Renderer *renderer, const std::string &text,
		const FontUtils&font, const SDL_Color &fgColor, const SDL_Color &bgColor) {
	constructFromText(renderer, text, font, &fgColor, &bgColor);
}

void TextureUtils::constructFromText(SDL_Renderer *renderer, const std::string &text,
		const FontUtils&font, const SDL_Color *fgColor, const SDL_Color *bgColor) {
	assert(renderer != nullptr);

	SDL_Surface *textSurface =
			bgColor == nullptr ?
					font.renderText(text, *fgColor) :
					font.renderText(text, *fgColor, *bgColor);

	if (textSurface == nullptr)
		throw "Couldn't create text: " + text;

	texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(textSurface);
		throw "Couldn't create text: " + text;
	}

	width_ = textSurface->w;
	height_ = textSurface->h;
	renderer_ = renderer;

}
