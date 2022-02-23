#pragma once

#include <string>
#include "GameObject.h"

using namespace std;
class MissionManager;


using namespace std;
class Mission
{
private:
	int maxReward_, minReward_, minDistance_, minTime_, iniTicks_;
	bool additionalReward_;
	string name_;
	MissionManager* manager_ = nullptr;
	GameObject* objective_ = nullptr;

public:

	Mission(MissionManager* manager, GameObject* o, int maxReward, int minReward, int minDistance, int minTime, string name);
	~Mission();

	//puede ser método interno
	void completeMission();
	void cancelAdditinalReward() { additionalReward_ = false; }
	bool updateState(GameObject* player);	

	string getName() { return name_; }

};

