#include "MissionObject.h"
#include "MissionsPanel.h"
#include "../Player/Player.h"
#include "../Items/Package.h"

#include "Game.h"

MissionObject::MissionObject(MissionsPanel* mp, Game* g) : GameObject(g, true), missionsPanel_(mp)
{
	active_ = false;

	setDimension(50, 50);
	setPosition(0, 0);

	this->texture = game->getTexture(missingTex);

}

MissionObject::~MissionObject()
{
	missionsPanel_ = nullptr;
}

void MissionObject::onPlayerInteraction(Player* player)
{
	if (active_) {
		game->getPlayer()->addMissionObject(new Package(game->getTexture(Item_Package), game, game->getPlayer()));
		changeActive(); // quitar del mapa
	}
}

void MissionObject::update()
{
}

void MissionObject::draw()
{
	if (active_) {
		//drawTexture(texture);
		SDL_Rect pos = getCollider();

		//Dibujamos respecto a la camara
		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();

		texture->render(pos);
	}
}

void MissionObject::setTexture(string tex)
{
	this->texture = game->getTexture(missingTex);

	//if (tex == "a") {
	//	this->texture = game->getTexture(a);
	//}
}
