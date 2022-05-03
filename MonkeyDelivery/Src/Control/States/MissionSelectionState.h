#pragma once

#include "State.h"

class MissionSelectionState : public State
{
public:
	MissionSelectionState(Game* game);
	MissionSelectionState(Game* game, vector<pair<string, string>> missionImg);
	~MissionSelectionState();

	void draw() override;
	inline void update() override {};
	inline void next() override {};

	string getStateName() const {
		return "Mission Selection state";
	};

	void registerCommands()override;

	void moveBox(int i);
	string getSelectedMission();

private:
	Texture* background_;
	Texture* controls_;

	vector<Texture*> allTextures_;
	vector<Texture*> currentTextures_;

	vector<string> missionData_;

	int currentSelection_; // misión que está seleccionada ahora mismo (en el vector)
	Texture* box_; // seleccionador
	int boxXPos_; // posición en la que está el seleccionador

	int xInc_ = 550; // separacion entre cada papel de mision
	int offsetX_, ySize_, wSize_, hSize_, h2Size_;
	int buttonsX_, buttonsY_, buttonsW_, buttonsH_;
};