#pragma once
#include "State.h"

class PauseState : public State
{
	Texture* backgroundTexture;
	Texture* selectorTexture;
	int buttonW = 300, buttonH = 140;

	int currentSelection = 0; // boton seleccionado (en el array buttonsUI)
public:
	PauseState(Game* game);
	~PauseState() = default;

	inline void update()override {};
	void draw()override;
	inline void next()override {};
	void onEnterState() override;

	void moveBox(Vector2D<int> i) override;
	inline Button* getCurrentButton() override { return buttonsUI[currentSelection]; };

	string getStateName() const {
		return "Pause state";
	};

	void registerCommands()override;
};