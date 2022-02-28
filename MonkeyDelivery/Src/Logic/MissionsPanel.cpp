#include "MissionsPanel.h"

MissionsPanel::MissionsPanel(Game* game) : GameObject(game)
{
	setTexture(missionPanelTexture);
}

void MissionsPanel::onPlayerInteraction(Player* player)
{
}

void MissionsPanel::onMissionSelected()
{
}
