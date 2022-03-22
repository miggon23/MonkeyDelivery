#pragma once
#include "../Utils/Vector2D.h"
#include <SDL.h>

class Game;

class Camera
{
private:
	Vector2D<float> pos_;
	float width_, height_; // Tamaño de la cámara
	float windowWidth_, windowHeight_;
	float scale_;

	Game* game_;
public:
	Camera(Game* g, Vector2D<float>& initialPos, float camW, float camH); // Doble & -> rvalue

	void Move(const Vector2D<float>& newPos);
	void MoveDir(const Vector2D<float>& newDir);
	void Lerp(const Vector2D<float>& newPos, float i);

	inline Vector2D<float> getCameraPosition() {
		return pos_;
	};
	Vector2D<float> getCameraCenterPosition();

	inline float getWidth() { return width_; };
	inline float getHeight() { return height_; };

	inline void setScale(float newScale) {
		scale_ = newScale;
	};
	inline float getScale() {
		return scale_;
	};

	inline void setPos(Vector2D<float> pos)
	{
		pos_ =  pos;
	}

	SDL_Rect renderRect();
};

