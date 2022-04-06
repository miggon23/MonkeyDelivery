#pragma once
#include "../utils/Vector2D.h"
#include "SDL.h"

class Game;

class Camera
{
private:
	Vector2D<double> pos_;
	double width_, height_; // Tamaño de la cámara
	double windowWidth_, windowHeight_;
	float scale_;

	Game* game_;
public:
	Camera(Game* g, const Vector2D<double>& initialPos, double camW, double camH);

	void Move(const Vector2D<double>& newPos);
	void MoveDir(const Vector2D<double>& newDir);
	void Lerp(const Vector2D<double>& newPos, float i);

	inline Vector2D<double> getCameraPosition() {
		return pos_;
	};
	Vector2D<double> getCameraCenterPosition();

	inline double getWidth() { return width_; };
	inline double getHeight() { return height_; };

	inline void setScale(float newScale) {
		scale_ = newScale;
	};
	inline float getScale() {
		return scale_;
	};

	inline void setPos(Vector2D<double> pos)
	{
		pos_ =  pos;
	}

	SDL_Rect renderRect();
};

