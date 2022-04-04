#pragma once
#include "../utils/Vector2D.h"
#include "SDL.h"

class Game;

class Camera
{
private:
	Vector2D<float> pos_;
	float width_, height_; // Tama�o de la c�mara
	float windowWidth_, windowHeight_;
	float scale_;

	Vector2D<float> iniOffset_, iniPos_;
	Game* game_;
public:
	Camera(Game* g, const Vector2D<float>& initialPos, float camW, float camH); // Doble & -> rvalue

	void calculateIniOffset(Point2D<float> pos);

	void Move(const Vector2D<float>& newPos);
	void MoveDir(const Vector2D<float>& newDir);
	void Lerp(const Vector2D<float>& newPos, float i);

	inline Vector2D<float> getCameraPosition() {
		return pos_;
	};

	inline Vector2D<float> getCameraCenterPosition() {
		return pos_ + Vector2D<float>(windowWidth_ / 2, windowHeight_ / 2); //-Vector2D<float>(windowWidth_ - width_, windowHeight_ - height_) / 2;
	}

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

	void setPosCenter(Vector2D<float> pos);

	const Vector2D<float> getRelativePos();

	

	SDL_Rect renderRect();
};

