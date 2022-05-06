#include "MissionsPanel.h"
#include "Game.h"

#include <cassert>
#include <memory>

#include "../Control/States/MissionSelectionState.h"
#include "../json/JSON.h"

#include "../Items/Package.h"
#include "DialogueBox.h"
#include "EndGameTarget.h"

#include "../Utils/Timer.h"

MissionsPanel::MissionsPanel(Game* game, AnimationManager* anim) : GameObject(game, true)
{
	Point2D<double> relative = { (double)(game->getWindowWidth() / 1800), (double)(game->getWindowHeight() / 1000) };

	setPosition(4005 * relative.getX(), 1125 * relative.getY());
	setDimension(108, 160);
	setTexture(MissionPanel_Interact);

	animationManager = anim;

	width_ = 34;
	height_ = 48;
	time_ = 300;
	maxX_ = 35;
	maxY_ = 0;
	textureRect = { 0, 0, width_, height_};
	timerAnimation_ = 0; // ¿puede ser const?

	missionsFinished_ = false;
	currentLevel_ = 1;
	levels_.reserve(NLEVELS_);
	for (int i = 0; i <= NLEVELS_; ++i) {
		levels_.push_back(0);
		levelsCompleted_.push_back(0);
	}

	loadMissions("Images/config/resources.json");
	
	activeTarget_ = new Target(this, game,animationManager);
	game->add(activeTarget_);

	missionObject_ = new MissionObject(this, game);
	game->add(missionObject_);
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
	// Si tengo una misión, no dejo acceder al panel
	if (currentMission_ != nullptr){
		game->newDialogue("MissionAlreadySelected");
	}
	else {
		if (!missionsFinished_) {

			vector<pair<string, string>> missionsSent;

			int a = 0;
			string b = "Mission";

			missionsSent.reserve(levels_[currentLevel_]);
			for (int i = 3*(currentLevel_-1) + 1; i <= 3*(currentLevel_); ++i) {
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
			game->newDialogue("MissionsFinished");
			auto endTarget = new EndGameTarget( game, animationManager);
			game->add(endTarget);
		}
	}
}

void MissionsPanel::update()
{
	if (currentMission_ != nullptr &&
		currentMission_->isExpress()) {
		if (getTime() <= 0) {
			// terminar misión express
			onMissionCompleted();
			dialogueEnd();
		}
		else if (getTime()/1000 == 10 ) { // cuando queden 10 s
			sdlutils().soundEffects().at("countdown").setVolume(game->getSoundEfectsVolume() * 2 * game->getGeneralVolume());
			sdlutils().soundEffects().at("countdown").play(0, 2);
		}
	}
}

void MissionsPanel::draw()
{
	auto pos = getCollider();
	pos.x -= (int)game->getCamera()->getCameraPosition().getX();
	pos.y -= (int)game->getCamera()->getCameraPosition().getY();

	animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
}

void MissionsPanel::onMissionSelected(string missionId)
{
	MissionInfo m = missions_.at(missionId);
	
	// solo se hace si no había una misión activa, es decir si el vecino no estaba activo
	if (!activeTarget_->isActive()) { //currentMission_ != nullptr

		// settear la misión como activa
		currentMission_ = new Mission(missionId, m.isExpress); 

		Point2D<double> relative = { (double)(game->getWindowWidth() / 1800), (double)(game->getWindowHeight() / 1000) };

		// comunicarlo al inventario o spawnear el objeto, dependiendo del tipo de misión
		if (m.isSpecial) {
			missionObject_->changeActive();
			missionObject_->setPosition(m.xObjPos*relative.getX(), m.yObjPos*relative.getY());
		}
		else {
			game->getPlayer()->addMissionObject(new Package(game->getTexture(Item_Package), game, game->getPlayer()));
		}
	
		// spawn Vecino
		activeTarget_->changeActive();
		activeTarget_->setDimension(m.width, m.height);

		activeTarget_->setPosition(m.xPos*relative.getX(), m.yPos*relative.getY());
		activeTarget_->setTexture(m.target);
		string txt = missionId;
		activeTarget_->setText(txt);
		missionObject_->setTexture(m.target);

		//iniciar el contador
		initialTicks_ =Uint32( game->getTimer()->TimeScale());
		endTime_ =  m.minTime;
	}

	// hide pannel
	game->InGame();
	State* tmp = game->getState();
	State* saved = game->getSavedState();
	game->setState(saved);
	game->removeSavedState();
	delete tmp;
}

void MissionsPanel::onMissionCompleted()
{
	// Quitar paquete
	game->getPlayer()->removeMissionObject();


	MissionInfo& m = missions_.at(currentMission_->getName());

	// Dar la recompensa
	int reward = m.maxMoney;

	// Restar dinero si se pasa del tiempo -> Resta 1 oro por segundo que se retrase
	auto ticks = SDL_GetTicks();
	if (ticks > (initialTicks_+endTime_)) {
		if (m.isExpress) {
			reward = 0;
		}else
			reward -= ((SDL_GetTicks() - initialTicks_ - m.minTime) / 1000); // valor de tiempo que se ha pasado del tiempo mínimo
	}
	endTime_ = 0; // resetea la variable

	if ( !m.isExpress && reward < m.minMoney) { // si no es express le aseguro un mínimo de dinero
		reward = m.minMoney;

		// sonido de ganar
		sdlutils().soundEffects().at("reward").setVolume(game->getSoundEfectsVolume() * 2 * game->getGeneralVolume());
		sdlutils().soundEffects().at("reward").play(0, 1);
	}

	game->changeMoneyPlayer(reward);

	// comprobar si todas las misiones de este nivel están completadas -> tandas de misiones
	levelsCompleted_[m.level]++;
	if (levelsCompleted_[m.level] == levels_[m.level]) {
		if (currentLevel_ != NLEVELS_) {
			game->addPickaxe(currentLevel_); // se le da la recompensa
			currentLevel_++;
			game->getShop()->actualice(currentLevel_);
			upgradeAchieved_ = true;
		}
		else {
			// terminar partida
			missionsFinished_ = true;
		}
	}

	// Marcar la mision como acabada
	m.completed = true;

	delete currentMission_;
	currentMission_ = nullptr;
}

void MissionsPanel::dialogueEnd()
{
	// Despawnear vecino -> cuando acabe el dialogo
	activeTarget_->changeActive();

	if (upgradeAchieved_) {
		game->newDialogue("Upgrade");
		upgradeAchieved_ = false;
	}
}

int MissionsPanel::getTime()
{
	return initialTicks_ + endTime_ - (int)game->getTimer()->TimeScale();
}

string MissionsPanel::getMissionImage()
{
	if (currentMission_ != nullptr) {

		MissionInfo m = missions_.at(currentMission_->getName());
		return m.helpImgRoute;
	}
	else
		return "No Mission Active";
}

string MissionsPanel::getMissionPaper()
{
	if (currentMission_ != nullptr) {

		MissionInfo m = missions_.at(currentMission_->getName());
		return m.imgRoute;
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
					int level = (int)vObj["level"]->AsNumber();
					std::string imgRoute = vObj["image"]->AsString(); 
					std::string helpImgRoute = vObj["helperImage"]->AsString();
					int maxMoney = (int)vObj["maxmoney"]->AsNumber();
					int minMoney = (int)vObj["minmoney"]->AsNumber();
					int minTime = (int)vObj["mintime"]->AsNumber();
					std::string target = vObj["target"]->AsString(); 
					double tX = vObj["targetPositionX"]->AsNumber();
					double tY = vObj["targetPositionY"]->AsNumber();
					double tW = vObj["targetWidth"]->AsNumber();
					double tH = vObj["targetHeight"]->AsNumber();
					bool isExpress = vObj["express"]->AsBool();
					bool isSpecial = vObj["special"]->AsBool();
					int oX = (int)vObj["objectPositionX"]->AsNumber();
					int oY = (int)vObj["objectPositionY"]->AsNumber();

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
						minTime,
						oX,
						oY
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