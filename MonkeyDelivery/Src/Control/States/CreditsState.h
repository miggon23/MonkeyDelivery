#pragma once
#include "State.h"

class CreditsState : public State
{
public:
	CreditsState(Game* game, Font* font);
	~CreditsState() = default;
	
	void draw()override;
	void update()override;

	void next()override;

	string getStateName() const {
		return "Credits state";
	};

	void registerCommands()override;

private:
	array<string, 10> credits_ =
	{
		"Elisa Todd",
		"Miguel Gonzales",
		"Antonio Povedano",
		"Adrián Montero",
		"Alejandro Segarra",
		"Simona Antonova",
		"Jacobo Alonso",
		"Javier Comas <JAvichu> ",
		"Sara ISABEL no me se el apellido (García)"
		"Raúl Saavedra"
	};

	Font* font_;
	Texture* wallpaper_;

	const int xOffset_ = 400, yOffset_ = 100, ySize_ = 50;
	const int timeNewName_ = 1000;

	int lastName_, index_ = 0;
};







