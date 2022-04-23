#include "MissionsPanel.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../Control/States/MissionSelectionState.h"
#include "../json/JSON.h"

#include "../Items/Package.h"
#include "DialogueBox.h"

MissionsPanel::MissionsPanel(Game* game) : GameObject(game, true)
{
	setPosition(2000, 650);
	setDimension(69, 98);
	setTexture(MissionPanel_Interact);

	missionsFinished_ = false;
	currentLevel_ = 1;
	levels_.reserve(NLEVELS_);
	for (int i = 0; i <= NLEVELS_; ++i) {
		levels_.push_back(0);
		levelsCompleted_.push_back(0);
	}

	loadMissions("Images/config/resources.json");
	
	activeTarget_ = new Target(this, game);
	game->add(activeTarget_);

}

MissionsPanel::~MissionsPanel()
{
	missions_.clear();
	if (currentMission_ != nullptr)
	{
		delete currentMission_;
		currentMission_ = nullptr;
	}
}

void MissionsPanel::onPlayerInteraction(Player* player)
{
	if (!missionsFinished_) {
		std::cout << "Activating Mission Selection State\n";

		vector<pair<string, string>> missionsSent;

		int a = 0;
		string b = "Mission";

		missionsSent.reserve(levels_[currentLevel_]);
		for (int i = levelsCompleted_[currentLevel_ - 1] + 1; i <= levelsCompleted_[currentLevel_ - 1] + levels_[currentLevel_]; ++i) {
			b += to_string(i);
			if (!missions_.at(b).completed) {
				missionsSent.push_back(make_pair(b, missions_.at(b).imgRoute));
			}
			b = "Mission";
		}


		// show pannel
		game->InGame();
		game->setSaveState(game->getState());
		game->setState(new MissionSelectionState(game, missionsSent));
	}
	else {
		// mostrar mensaje de que ya no quedan más misiones
		string a = "MissionsFinished";
		game->newDialogue(a);
	}
}


void MissionsPanel::update()
{
	if (currentMission_ != nullptr &&
		currentMission_->isExpress() &&
		getTime() <= 0) {

		// terminar misión express
		onMissionCompleted();
	}
}

void MissionsPanel::onMissionSelected(string missionId)
{
	std::cout << "Deactivating Mission Selection State\n";

	MissionInfo m = missions_.at(missionId);
	
	// solo se hace si no había una misión activa, es decir si el vecino no estaba activo
	if (!activeTarget_->isActive()) { //currentMission_ != nullptr

		// settear la misión como activa
		currentMission_ = new Mission(missionId, m.isExpress); 

		// comunicarlo al inventario o spawnear el objeto, dependiendo del tipo de misión
		game->getPlayer()->addMissionObject(new Package(game->getTexture(Item_Package), game, game->getPlayer()));
	
		//Misiones express
		endTime_ = initialTicks_ + m.minTime;

		// spawn Vecino
		activeTarget_->changeActive();
		activeTarget_->setDimension(m.width, m.height);
		activeTarget_->setPosition(m.xPos, m.yPos);
		activeTarget_->setTexture(m.target);
		string txt = missionId;
		activeTarget_->setText(txt);

		//iniciar el contador
		initialTicks_ = SDL_GetTicks();
	}

	// hide pannel
	game->InGame();
	State* tmp = game->getState();
	State* saved = game->getSavedState();
	saved->resetInitTime();
	saved->registerCommands();
	game->setState(saved);
	game->removeSavedState();
	delete tmp;
	//delete tmp;
}

void MissionsPanel::onMissionCompleted()
{
	MissionInfo& m = missions_.at(currentMission_->getName());
	// Dar la recompensa
	int reward = m.maxMoney;

	// Restar dinero si se pasa del tiempo -> Resta 1 oro por segundo que se retrase
	if (SDL_GetTicks() > endTime_) {
		reward -= ((SDL_GetTicks() - initialTicks_ - m.minTime) / 1000); // valor de tiempo que se ha pasado del tiempo mínimo
	}
	endTime_ = 0; // resetea la variable

	if (m.isExpress && reward < 0) { // si es express y se ha retrasado tanto que el dinero es negativo
		reward = 0;
	}
	else if (reward < m.minMoney) { // si no es express le aseguro un mínimo de dinero
		reward = m.minMoney;
	}

	game->changeMoneyPlayer(reward);

	// Marcar la mision como acabada
	m.completed = true;

	delete currentMission_;
	currentMission_ = nullptr;

	// Despawnear vecino
	activeTarget_->changeActive();

	// Quitar paquete
	game->getPlayer()->removeMissionObject();

	// comprobar si todas las misiones de este nivel están completadas -> tandas de misiones
	levelsCompleted_[m.level]++;
	if (levelsCompleted_[m.level] == levels_[m.level]) {
		if (currentLevel_ != NLEVELS_) {
			currentLevel_++;
		}
		else {
			// terminar partida
			missionsFinished_ = true;
		}
	}
}

string MissionsPanel::getMissionImage()
{
	if (currentMission_ != nullptr) {

		MissionInfo m = missions_.at(currentMission_->getName());
		std::cout << m.helpImgRoute;
		return m.helpImgRoute;
	}
	else
		return "No Mission Active";
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
					std::string helpImgRoute = vObj["helperImage"]->AsString();
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

				/* switch (level)
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
					}*/

					levels_[level]++;

					MissionInfo m = {
						level,
						false,
						isExpress,
						isSpecial,
						imgRoute,
						helpImgRoute,
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