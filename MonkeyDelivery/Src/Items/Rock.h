#pragma once
#include "../Logic/ColliderTile.h"

class Rock : public ColliderTile {
	int w=75.0;
	int h=75.0;
	int levelToDestroy_;
public:
	Rock(Game* game, int x, int y,int level);
	~Rock();	
	inline int seeLevelToDestroy() { return levelToDestroy_; };
	void draw() override;
};