// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_ttf.h>
#include <string>
#include <cassert>
#include <iostream>

#include "macros.h"

class FontUtils {
public:

	// cannot copy objects of this type!
	FontUtils(const FontUtils&other) = delete;
	FontUtils& operator=(const FontUtils&other) = delete;

	// can be moved
	FontUtils& operator=(FontUtils&&other) noexcept {
		this->~FontUtils();
		font_ = other.font_;
		other.font_ = nullptr;
		return *this;
	}

	FontUtils(FontUtils&&other) noexcept {
		font_ = other.font_;
		other.font_ = nullptr;
	}

	FontUtils(const std::string &fileName, int size) {
		font_ = TTF_OpenFont(fileName.c_str(), size);
		if (font_ == nullptr) {
			throw "Couldn't load font: " + fileName;
		}
	}

	virtual ~FontUtils() {
		if (font_ != nullptr)
			TTF_CloseFont(font_);
	}

	inline SDL_Surface* renderText(const std::string &text,
			SDL_Color fgColor) const {
		assert(font_ != nullptr);
		return TTF_RenderUTF8_Solid(font_, text.c_str(), fgColor);
	}

	inline SDL_Surface* renderText(const std::string &text, SDL_Color fgColor,
			SDL_Color bgColor) const {
		assert(font_ != nullptr);
		return TTF_RenderUTF8_Shaded(font_, text.c_str(), fgColor, bgColor);
	}

private:
	TTF_Font *font_;
};