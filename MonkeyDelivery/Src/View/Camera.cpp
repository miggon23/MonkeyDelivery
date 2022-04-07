#include "Camera.h"
#include "../Logic/Game.h"
#include <iostream>

Camera::Camera(Game* g, const Vector2D<double>& initialPos, double camW, double camH)
{
	game_ = g;
	pos_ = initialPos;

	height_ = camH;
	width_ = camW;

	windowHeight_ = game_->getWindowHeight();
	windowWidth_ = game_->getWindowWidth();
	
	scale_ = windowWidth_ / width_;
}

void Camera::Move(const Vector2D<double>& newPos)
{
	pos_ = newPos;
}

void Camera::MoveDir(const Vector2D<double>& newDir)
{
	pos_ = pos_ + newDir;
}

void Camera::Lerp(const Vector2D<double>& newPos, float i)
{
	// se pone el origen en la esquina superior izquierda
	auto n = newPos - Vector2D<double>(windowWidth_ / 2, windowHeight_ / 2) + Vector2D<double>(windowWidth_ - width_, windowHeight_ - height_) / 2;
	if ((pos_ - n).magnitude() > 2)
		pos_ = pos_ + (newPos - pos_) * i;
}

Vector2D<double> Camera::getCameraCenterPosition()
{
	return pos_ + Vector2D<double>(windowWidth_ / 2, windowHeight_ / 2) - Vector2D<double>(windowWidth_ - width_, windowHeight_ - height_) / 2;
}

SDL_Rect Camera::renderRect()
{
	SDL_Rect r = SDL_Rect{ (int )round(pos_.getX()), (int) round(pos_.getY()), (int)width_, (int)height_ };
	return r;
}