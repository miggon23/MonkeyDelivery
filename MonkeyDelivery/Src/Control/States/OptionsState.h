#pragma once
#include "State.h"
#include "../../Logic/Game.h"
#include "../States/MenuState.h"
class OptionsState : public State
{
	Texture* selectorTexture;	
	Texture* backgroundTexture;
	Texture* signsTexture;
	const int buttonW = 300, buttonH = 140;

	const int selectorW = 300, selectorH = 140;

	int currentSelection = 0; // slider seleccionado (en el array slidersUI)
public:
	OptionsState(Game* game/*, int num*/);
	~OptionsState() = default;

	void update()override;
	void draw()override;
	void next()override;

	void moveBox(Vector2D<int> i) override;
	inline Button* getCurrentButton() override { 
		if (currentSelection == 4) // en esta pantalla solo está este botón
			return buttonsUI[0];
		else
			return nullptr;
	}; 

	string getStateName() const {
		return "Options state";
	};

	void registerCommands()override;
};


