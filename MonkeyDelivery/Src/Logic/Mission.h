#pragma once

#include <string>
#include "GameObject.h"

using namespace std;
class MissionManager;


using namespace std;
class Mission
{
private:
	int maxReward_, minReward_, minDistance_;
	string name_;
	MissionManager* manager_ = nullptr;
	GameObject* objetive_ = nullptr;

public:

	Mission(MissionManager* manager, GameObject* o, int maxReward, int minReward, int minDistance, string name);
	~Mission();

	//puede ser método interno
	void completeMission();
	bool updateState(GameObject* player);	

	string getName() { return name_; }

};

