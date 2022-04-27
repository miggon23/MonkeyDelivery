#pragma once
#include "../Logic/GameObject.h"
class Game;

class FearLevel: public GameObject {
private:
	
	float place_;
	double fear_;
	double maxFear_;

	int x, y, w, h;

public:
	FearLevel(Game* game);
	~FearLevel() { };

	void update() override {};
	bool getScared(double amount);
	void resetFear();
	void draw() override;

	inline double percentFear() { return (fear_ / maxFear_) * 100; };
	inline double getFear() { return fear_; };
};