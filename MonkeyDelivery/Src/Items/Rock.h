#pragma once
#include "../Logic/ColliderTile.h"

class Rock : public ColliderTile {
	const double width_= 75.0;
	const double height = 75.0;
	int levelToDestroy_;
public:
	Rock(Game* game, int x, int y,int level);
	~Rock();	
	inline int seeLevelToDestroy() { return levelToDestroy_; };
	void draw() override;
};