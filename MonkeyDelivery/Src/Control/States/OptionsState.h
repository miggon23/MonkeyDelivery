#pragma once
#include "State.h"
#include "../../Logic/Game.h"
#include "../States/MenuState.h"
#include "../UI/Sliders/Slider.h"
class OptionsState : public State
{
	Slider* slider;
public:
	OptionsState(Game* game);
	~OptionsState() = default;

	void update()override;
	void draw()override;
	void next()override;

	string getStateName() const {
		return "Options state";
	};

	void registerCommands()override;
};


