#pragma once
#include <vector>
#include "Mission.h"

using namespace std;

class Game;
class MissionManager
{
private:
	Game* game_;
	vector<Mission*> listMission_;
	Mission* currentMission_ = nullptr;
	
public:

	MissionManager(Game* game) : game_(game) {};
	~MissionManager();

	void AddMission(Mission* mission);
	void checkCurrentMission();

	Mission* currentMisssion() { return currentMission_; }
	Game* getGame() { return game_; }
	
};

