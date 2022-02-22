#include "Mission.h"
#include "Game.h"
#include "MissionManager.h"
#include <math.h>


Mission::Mission(MissionManager* manager, GameObject* objective, int maxReward, int minReward, int minDistance, int minTime, string name)
{
	objective_ = objective;
	maxReward_ = maxReward;
	minReward_ = minReward;
	minDistance_ = minDistance;
	manager_ = manager;
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

	manager_->getGame()->changeMoneyPlayer(reward);
}

bool Mission::updateState(GameObject* player)
{
	/*if (abs(player->getX() - objective_->getX()) + abs(player->getY() - objective_->getY()) <= minDistance_)
	{
		completeMission();
		return true;
	}*/

	if (player->collide(objective_->getCollider())) {
		completeMission();
		return true;
	}

	return false;
}
