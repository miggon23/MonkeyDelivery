#pragma once
#include "GameObject.h"
#include "Mission.h"

// Clase que lleva control de las misiones, el nivel actual, y más adelante el fin del juego
class MissionsPanel : public GameObject
{
private:
	int currentLevel_; // nivel de misiones en el que se está
	Mission* currentMission_; // Misión activa

public:
	MissionsPanel(Game* game);
	~MissionsPanel();
	// Debe activar el estado SeleccionDeMisión con ciertos parámetros que mira en el JSON
	void onPlayerInteraction(Player* player) override;
	
	// llamado desde el estado de SeleccionDeMisión, cuando se sale de él
	void onMissionSelected();
};

