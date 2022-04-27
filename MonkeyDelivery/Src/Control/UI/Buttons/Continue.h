#pragma once
#include "../../Button.h"

class Continue : public Button
{
public:
	Continue(int x, int y, double w, double h, Game* game);
	~Continue() {};
	void onCursorCollision() override;
};