#include "MissionManager.h"
#include "Game.h"

MissionManager::~MissionManager()
{
	currentMission_ = nullptr;
	game_ = nullptr;

	for (auto mission : listMission_)
	{
		delete mission;
	}
	listMission_.clear();	
}

void MissionManager::AddMission(Mission* mission)
{
	listMission_.push_back(mission);

	if (currentMission_ == nullptr)
		currentMission_ = mission;
}

void MissionManager::checkCurrentMission()
{
	if (currentMission_ != nullptr)
	{
		if (currentMission_->updateState(game_->getPlayer()))
			currentMission_ = nullptr;
	}
		
}

string MissionManager::getMissionName()
{
	if (currentMission_ != nullptr)
		return currentMission_->getName();
	else
		return " ";
}
	
