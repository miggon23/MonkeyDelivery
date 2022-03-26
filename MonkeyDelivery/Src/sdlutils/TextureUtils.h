// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <cassert>
#include <iostream>

#include "FontUtils.h"

class TextureUtils {
public:

	// cannot copy textures
	TextureUtils(const TextureUtils&) = delete;
	TextureUtils& operator=(const TextureUtils&) = delete;

	// can be moved
	TextureUtils& operator=(TextureUtils&&other) noexcept;
	TextureUtils(TextureUtils&&other) noexcept;

	// Construct from image
	TextureUtils(SDL_Renderer *renderer, const std::string &fileName);

	// Construct from text
	TextureUtils(SDL_Renderer *renderer, const std::string &text, const FontUtils&font,
			const SDL_Color &fgColor);

	// Construct from text with background
	TextureUtils(SDL_Renderer *renderer, const std::string &text, const FontUtils&font,
			const SDL_Color &fgColor, const SDL_Color &bgColor);


	virtual ~TextureUtils() {
		if (texture_ != nullptr)
			SDL_DestroyTexture(texture_); // delete the SDL texture
	}

	inline int width() const {
		return width_;
	}

	inline int height() const {
		return height_;
	}

	inline SDL_Texture* getSDLTexture() { return texture_; };

	// This rendering method corresponds to method SDL_RenderCopyEx.
	//
	// Renders part of the texture (src) to a destination rectangle (dest)
	// with a rotation (angle) around point p (of dest), and flips
	// according to the value of flip. If 'p'is nullptr, the rotation is done
	// wrt. the center
	//
	inline void render(const SDL_Rect &src, const SDL_Rect &dest, double angle,
			const SDL_Point *p = nullptr,
			SDL_RendererFlip flip = SDL_FLIP_NONE) {
		assert(texture_ != nullptr);
		SDL_RenderCopyEx(renderer_, texture_, &src, &dest, angle, p, flip);
	}

	// This rendering method corresponds to method SDL_RenderCopy.
	//
	// Renders part of the texture (src) to a destination rectangle (dest).
	// It can be implemented by calling the previous render method as well,
	// but we use SDL_RenderCopy directly since it does less checks so it
	// saves some checks ...
	inline void render(const SDL_Rect &src, const SDL_Rect &dest) {
		assert(texture_ != nullptr);
		SDL_RenderCopy(renderer_, texture_, &src, &dest);
	}

	// render the complete texture at position (x,y).
	inline void render(int x, int y) {
		SDL_Rect dest = { x, y, width_, height_ };
		render(dest);
	}

	// renders the complete texture at a destination rectangle (dest)
	inline void render(const SDL_Rect &dest) {
		SDL_Rect src = { 0, 0, width_, height_ };
		render(src, dest);
	}

	// renders the complete texture at a destination rectangle (dest),
	// with rotation
	inline void render(const SDL_Rect &dest, float rotation) {
		SDL_Rect src = { 0, 0, width_, height_ };
		render(src, dest, rotation);
	}

private:

	// Construct from text
	void constructFromText(SDL_Renderer *renderer, const std::string &text,
			const FontUtils&font, const SDL_Color *fgColor,
			const SDL_Color *bgColor = nullptr);

	SDL_Texture *texture_;
	SDL_Renderer *renderer_;
	int width_;
	int height_;
};
