#include "MissionsPanel.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../Control/States/MissionSelectionState.h"
#include "../json/JSON.h"

#include "Package.h"

MissionsPanel::MissionsPanel(Game* game) : GameObject(game)
{
	setPosition(150, 200);
	setDimension(120, 150);
	setTexture(missionPanelTexture);

	loadMissions("../Images/config/resources.json");

	currentLevel_ = 1;

	activeTarget_ = new Target(this, game);
	game->add(activeTarget_);
}

MissionsPanel::~MissionsPanel()
{
	missions_.clear();
	delete currentMission_;
	currentMission_ = nullptr;
}

void MissionsPanel::onPlayerInteraction(Player* player)
{
	std::cout << "Activating Mission Selection State\n";

	vector<pair<string, string>> missionsSent;

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
		missionsSent.push_back(make_pair(b, missions_.at(b).imgRoute));
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
	
	// solo se hace si no había una misión activa, es decir si el vecino no estaba activo
	if (!activeTarget_->isActive()) { //currentMission_ != nullptr

		// settear la misión como activa
		currentMission_ = new Mission(activeTarget_, m.maxMoney, m.minMoney, 10, m.minTime, missionId); 
		
		// comunicarlo al inventario o spawnear el objeto, dependiendo del tipo de misión
		game->getPlayer()->addMissionObject(new Package);
	
		// spawn Vecino
		activeTarget_->changeActive();
		activeTarget_->setDimension(m.width, m.height);
		activeTarget_->setPosition(m.xPos, m.yPos);
		activeTarget_->setTexture(m.target);

		//iniciar el contador
		initialTicks_ = SDL_GetTicks();
	}
	

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
	MissionInfo m = missions_.at(currentMission_->getName());
	// Dar la recompensa
	int reward = m.maxMoney;

	// Restar dinero si se pasa del tiempo -> Resta 1 oro por segundo que se retrase
	if (SDL_GetTicks() > initialTicks_ + m.minTime) {
		reward -= ((SDL_GetTicks() - initialTicks_ - m.minTime) / 1000); // valor de tiempo que se ha pasado del tiempo mínimo
	}

	// Le aseguro un mínimo de dinero
	if (reward < m.minMoney) reward = m.minMoney; 

	game->changeMoneyPlayer(reward);

	// Marcar la mision como acabada
	missions_.at(currentMission_->getName()).completed = true;
	currentMission_->completeMission();
	delete currentMission_;
	currentMission_ = nullptr;

	// Despawnear vecino
	activeTarget_->changeActive();

	// comprobar si todas las misiones de este nivel están completadas -> tandas de misiones
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
					std::string imgRoute = vObj["image"]->AsString(); 
					int maxMoney = vObj["maxmoney"]->AsNumber();
					int minMoney = vObj["minmoney"]->AsNumber();
					int minTime = vObj["mintime"]->AsNumber();
					std::string target = vObj["target"]->AsString(); 
					int tX = vObj["targetPositionX"]->AsNumber();
					int tY = vObj["targetPositionY"]->AsNumber();
					int tW = vObj["targetWidth"]->AsNumber();
					int tH = vObj["targetHeight"]->AsNumber();
					bool isExpress = vObj["express"]->AsBool();
					bool isSpecial = vObj["special"]->AsBool();

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
						tX,
						tY,
						tW,
						tH,
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
