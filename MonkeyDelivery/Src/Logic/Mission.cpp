#include "Mission.h"
#include "Game.h"
#include "MissionManager.h"
#include <math.h>


Mission::Mission(Target* objective, int maxReward, int minReward, int minDistance, int minTime, string name)
{
	objective_ = objective;
	maxReward_ = maxReward;
	minReward_ = minReward;
	minDistance_ = minDistance;
	minTime_ = minTime * 1000;
	name_ = name;
	additionalReward_ = true;
	iniTicks_ = SDL_GetTicks();

}

Mission::~Mission()
{
	objective_ = nullptr;
}

void Mission::completeMission()
{
	int reward = minReward_;
	if (additionalReward_ && SDL_GetTicks() < iniTicks_ + minTime_)
		reward = maxReward_;
}

void Mission::setExpress()
{
}
