#include "Camera.h"
#include "../Logic/Game.h"
#include <iostream>

Camera::Camera(Game* g, const Vector2D<float>& initialPos, float camW, float camH)
{
	game_ = g;
	pos_ = initialPos;

	height_ = camH;
	width_ = camW;

	windowHeight_ = sdlutils().width();
	windowWidth_ = sdlutils().height();
	
	scale_ = windowWidth_ / width_;

	iniPos_ = pos_;
}

void Camera::calculateIniOffset(Point2D<float> pos)
{
	iniOffset_ = pos - pos_;
}

void Camera::Move(const Vector2D<float>& newPos)
{
	pos_ = newPos;
}

void Camera::MoveDir(const Vector2D<float>& newDir)
{
	pos_ = pos_ + newDir;
}

void Camera::Lerp(const Vector2D<float>& newPos, float i)
{
	// se pone el origen en la esquina superior izquierda
	auto n = newPos - Vector2D<float>(windowWidth_ / 2, windowHeight_ / 2) + Vector2D<float>(windowWidth_ - width_, windowHeight_ - height_) / 2;
	if ((pos_ - n).magnitude() > 2)
		pos_ = pos_ + (newPos - pos_) * i;
}


void Camera::setPosCenter(Vector2D<float> pos)
{
	pos_ = pos - iniOffset_ ;
}

const Vector2D<float> Camera::getRelativePos()
{
	return (pos_ - iniPos_);
}



SDL_Rect Camera::renderRect()
{
	return SDL_Rect{ (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ };
}

