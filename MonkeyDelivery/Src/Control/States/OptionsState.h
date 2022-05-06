#pragma once
#include "State.h"
#include "../../Logic/Game.h"
#include "../States/MenuState.h"
class OptionsState : public State
{
	Texture* selectorTexture;	
	Texture* backgroundTexture;
	Texture* signsTexture;
	int buttonW = 300, buttonH = 140;

	int currentSelection = 0; // slider seleccionado (en el array slidersUI)

	int index_ = 0;
public:
	OptionsState(Game* game);
	~OptionsState() = default;

	void update()override;
	void draw()override;
	inline void next()override {};

	inline Button* getCurrentButton() override { 
		// en esta pantalla solo está este botón
		return buttonsUI[0];
	}; 

	string getStateName() const {
		return "Options state";
	};

	void registerCommands()override;
};