#pragma once
#include <vector>
#include <string>
#include "Mission.h"
#include "../Logic/DialogueBox.h"

using namespace std;

class Game;
class MissionManager
{
private:
	Game* game_;
	vector<Mission*> listMission_;
	Mission* currentMission_ = nullptr;

	
public:

	MissionManager(Game* game);
	~MissionManager();

	void AddMission(Mission* mission);
	void checkCurrentMission();  

	inline Mission* currentMisssion() { return currentMission_; }
	inline Game* getGame() { return game_; }
	
	string getMissionName();
};

