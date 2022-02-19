#include "Mission.h"
#include "Game.h"
#include "MissionManager.h"
#include <math.h>


Mission::Mission(MissionManager* manager, GameObject* objetive, int maxReward, int minReward, int minDistance)
{
	objetive_ = objetive;
	maxReward_ = maxReward;
	minReward_ = minReward;
	minDistance_ = minDistance;
	manager_ = manager;

}

Mission::~Mission()
{
	objetive_ = nullptr;
}

void Mission::completeMission()
{
	manager_->getGame()->changeMoneyPlayer(minReward_);
}

bool Mission::updateState(GameObject* player)
{
	if (abs(player->getX() - objetive_->getX()) + abs(player->getY() - objetive_->getY()) <= minDistance_)
	{
		completeMission();
		return true;
	}

	return false;
}
