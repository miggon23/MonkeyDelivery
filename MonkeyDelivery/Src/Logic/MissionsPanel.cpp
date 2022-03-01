#include "MissionsPanel.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../Control/States/MissionSelectionState.h"
#include "../json/JSON.h"


MissionsPanel::MissionsPanel(Game* game) : GameObject(game)
{
	setTexture(missionPanelTexture);
	loadMissions("../Images/config/resources.json");
}

MissionsPanel::~MissionsPanel()
{
}

void MissionsPanel::onPlayerInteraction(Player* player)
{
	if (game->getSavedState() == nullptr) {
		// show pannel
		game->saveState(game->getState());
		game->setState(new MissionSelectionState(game));
	}
}

void MissionsPanel::update()
{
	missions_.clear();
}

void MissionsPanel::onMissionSelected()
{
	// Esto se lee del JSON según un parámetro que se va a pasar a este método
	currentMission_ = new Mission(game->getMissionManager(), game->getiE(), 100, 100, 10, 1000, "Misión 1"); 

	// hide pannel
	State* tmp = game->getState();
	State* saved = game->getSavedState();
	saved->resetInitTime();
	saved->registerCommands();
	game->setState(saved);
	game->clearSavedState();
	delete tmp;

	// spawn Vecino

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
