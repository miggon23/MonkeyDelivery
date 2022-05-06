#pragma once
#include "State.h"

class MapState : public State
{
	const int CUT_OFF = 402;
public:
	MapState(Game* game);
	~MapState();

	void update()override {};
	void draw()override;
	void next()override {};

	string getStateName() const {
		return "Map state";
	};

	void registerCommands()override;

private:

	Texture* backgroundTex_;
	Texture* leyendaTex_;
	Texture* missionTex_;
	
	int x_, y_;
};