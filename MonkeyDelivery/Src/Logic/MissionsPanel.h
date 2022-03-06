#pragma once
#include "GameObject.h"
#include "Mission.h"
#include "Target.h"
#include <map>

struct MissionInfo {
	int level;
	bool completed;
	bool isExpress;
	bool isSpecial;
	string imgRoute;
	string target;
	double xPos;
	double yPos;
	double width;
	double height;
	int maxMoney;
	int minMoney;
	int minTime;
};

using sdl_resource_table = std::map<std::string, MissionInfo>;

// Clase que lleva control de las misiones, el nivel actual, y m�s adelante el fin del juego
class MissionsPanel : public GameObject
{
private:
	int currentLevel_; // nivel de misiones en el que se est�
	Mission* currentMission_; // Misi�n activa

	sdl_resource_table missions_; // Missions map (string -> mission)

	// N� de misiones de cada nivel que hay
	int nLevel1_;
	int nLevel2_;
	int nLevel3_;

	// Vecino activo
	Target* activeTarget_;

	Uint32 initialTicks_; // valor de los ticks cuando se activ� la misi�n
	
public:
	MissionsPanel(Game* game);
	~MissionsPanel();
	// Debe activar el estado SeleccionDeMisi�n con ciertos par�metros que mira en el JSON
	void onPlayerInteraction(Player* player) override;
	void update() override;

	// llamado desde el estado de SeleccionDeMisi�n, cuando se sale de �l
	void onMissionSelected(string missionId);

	// llamado desde el target (vecino) cuando interact�e y la misi�n se complete
	void onMissionCompleted();

	// el map en el que se guarda la info de las misiones
	inline sdl_resource_table getMissions() {
		return missions_;
	}

	void loadMissions(std::string filename);

	inline Mission* getCurrentMission() { return currentMission_; };

	inline Target* getTarget() { return activeTarget_; };
};

