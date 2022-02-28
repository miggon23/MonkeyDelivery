#pragma once
#include "GameObject.h"
#include "Mission.h"

// Clase que lleva control de las misiones, el nivel actual, y m�s adelante el fin del juego
class MissionsPanel : public GameObject
{
private:
	int currentLevel_; // nivel de misiones en el que se est�
	Mission* currentMission_; // Misi�n activa

public:
	MissionsPanel(Game* game);
	~MissionsPanel();
	// Debe activar el estado SeleccionDeMisi�n con ciertos par�metros que mira en el JSON
	void onPlayerInteraction(Player* player) override;
	
	// llamado desde el estado de SeleccionDeMisi�n, cuando se sale de �l
	void onMissionSelected();
};
