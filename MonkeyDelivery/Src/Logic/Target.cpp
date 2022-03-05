#include "Target.h"
#include "MissionsPanel.h"
#include "Player.h"

Target::Target(MissionsPanel* mp, Game* g) : GameObject(g), missionsPanel_(mp)
{
	//missionsPanel_->getCurrentMission()->getName();
	active_ = false;

	setDimension(120, 150);
	setPosition(500, 80);
	setTexture(tucanTexture);

}

Target::~Target()
{
}

void Target::onPlayerInteraction(Player* player)
{
	/*if (player->tieneElObjeto()) {

	}*/
	missionsPanel_->onMissionCompleted();
}

void Target::update()
{
}
