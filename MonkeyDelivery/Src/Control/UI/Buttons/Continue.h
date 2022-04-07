#pragma once
#include "../../Button.h"

class Continue : public Button
{
public:
	Continue(int x, int y, int w, int h, Game* game);
	~Continue() {};
	void onCursorCollision() override;
};