#include "Target.h"
#include "MissionsPanel.h"
#include "../Player/Player.h"
#include "Game.h"

Target::Target(MissionsPanel* mp, Game* g) : GameObject(g, true), missionsPanel_(mp)
{
	active_ = false;

	setDimension(1, 1);
	setPosition(0, 0);

}

Target::~Target()
{
	missionsPanel_ = nullptr;
}

void Target::onPlayerInteraction(Player* player)
{
	if (active_) {

		if (player->hasMissionObject()) {

			game->newMissionDialogue(textPath_);

			player->removeMissionObject();
			missionsPanel_->onMissionCompleted();
		}
		else {
			// activar un dialogo que diga que busques su paquete
		}
	}
}

void Target::update()
{
}

void Target::draw() {
	if (active_) {
		//drawTexture(texture);
		 SDL_Rect pos = getCollider();

        //Dibujamos respecto a la camara
        pos.x -= (int)game->getCamera()->getCameraPosition().getX();
        pos.y -= (int)game->getCamera()->getCameraPosition().getY();

        texture->render(pos);
	}
}

void Target::setTexture(string tex)
{
	if (tex == "NPC_Tucan") {
		texture = game->getTexture(npc_Tucan);
	}else if (tex == "NPC_Coco") {
		texture = game->getTexture(npc_Coco);
	}else if (tex == "NPC_Eagle") {
		texture = game->getTexture(npc_Eagle);
	}else if (tex == "NPC_Fish") {
		texture = game->getTexture(npc_Fish);
	}else if (tex == "NPC_Fox") {
		texture = game->getTexture(npc_Fox);
	}else if (tex == "NPC_Frog") {
		texture = game->getTexture(npc_Frog);
	}else if (tex == "NPC_Hipo") {
		texture = game->getTexture(npc_Hipo);
	}else if (tex == "NPC_Pavo") {
		texture = game->getTexture(npc_Pavo);
	}else if (tex == "NPC_Rabbit") {
		texture = game->getTexture(npc_Rabbit);
	}

	// forma antigua, sin texture container
	//if (texture != nullptr)
	//	delete texture;
	//string route = "./Images/NPCs/" + tex + ".png";
	//texture = new Texture(game->getRenderer(), route);
}