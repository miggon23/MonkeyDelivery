#include "MissionsPanel.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../Control/States/MissionSelectionState.h"
#include "../json/JSON.h"


MissionsPanel::MissionsPanel(Game* game) : GameObject(game)
{
	setPosition(350, 200);
	setDimension(120, 150);
	setTexture(missionPanelTexture);

	loadMissions("../Images/config/resources.json");

	currentLevel_ = 1;
}

MissionsPanel::~MissionsPanel()
{
	missions_.clear();
	//delete currentMission_; cuando se cambie la estructura habrá que poner esto
}

void MissionsPanel::onPlayerInteraction(Player* player)
{
	std::cout << "Activating Mission Selection State\n";

	vector<string> missionsSent;

	int a = 0;
	string b = "Mission";
	int numMissions = 0;

	switch (currentLevel_) {
	case 1:
		a = 1;
		numMissions = nLevel1_;
		break;
	case 2:
		a = nLevel1_ + 1;
		numMissions = nLevel2_;

		break;
	case 3:
		a = nLevel2_ + 1;
		numMissions = nLevel3_;
		break;
	}

	missionsSent.reserve(numMissions);
	for (int i = a; i <= numMissions; ++i) {
		b += to_string(i);
		missionsSent.push_back(missions_.at(b).imgRoute);
		//missionsSent.push_back(b);
		b = "Mission";
	}

	if (game->getSavedState() == nullptr) {
		// show pannel
		game->saveState(game->getState());
		game->setState(new MissionSelectionState(game, missionsSent));
	}
}

void MissionsPanel::update()
{
}

void MissionsPanel::onMissionSelected(string missionId)
{
	std::cout << "Deactivating Mission Selection State\n";

	MissionInfo m = missions_.at(missionId);
	
	// spawn Vecino
	

	// settear la misión como activa
	currentMission_ = new Mission(game->getMissionManager(), game->getiE(), m.maxMoney, m.minMoney, 10, m.minTime, missionId); 
	game->setActiveMission(currentMission_); // por la forma en que está gestionado ahora
	
	// hide pannel
	State* tmp = game->getState();
	State* saved = game->getSavedState();
	saved->resetInitTime();
	saved->registerCommands();
	game->setState(saved);
	game->clearSavedState();
	delete tmp;


}

void MissionsPanel::onMissionCompleted()
{
	missions_.at(currentMission_->getName()).completed = true;

	// comprobar si todas las misiones de este nivel están completadas
}

void MissionsPanel::loadMissions(std::string filename)
{
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	jValue = root["missions"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();

					std::string key = vObj["id"]->AsString();
					int level = vObj["level"]->AsNumber();
					bool isExpress = vObj["express"]->AsBool();
					bool isSpecial = vObj["special"]->AsBool();
					std::string imgRoute = vObj["image"]->AsString(); 
					std::string target = vObj["target"]->AsString(); 
					int maxMoney = vObj["maxmoney"]->AsNumber();
					int minMoney = vObj["minmoney"]->AsNumber();
					int minTime = vObj["mintime"]->AsNumber();

					switch (level)
					{
					case 1:
						nLevel1_ += 1;
						break;
					case 2:
						nLevel2_ += 1;
						break;
					case 3:
						nLevel3_ += 1;
						break;
					default:
						break;
					}

					MissionInfo m = {
						level,
						false,
						isExpress,
						isSpecial,
						imgRoute,
						target,
						maxMoney,
						minMoney,
						minTime
					};
#ifdef _DEBUG
					std::cout << "Loading mission with id: " << key << std::endl;
#endif
					missions_.emplace(std::make_pair(key, m));
				}
				else {
					throw "'missions' array in '" + filename
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'fonts' is not an array in '" + filename + "'";
		}
	}
}
