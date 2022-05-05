#include "Target.h"
#include "MissionsPanel.h"
#include "../Player/Player.h"
#include "Game.h"

Target::Target(MissionsPanel* mp, Game* g, AnimationManager* animation) : GameObject(g, true), missionsPanel_(mp), animationManager(animation)
{
	active_ = false;

	setDimension(1, 1);
	setPosition(0, 0);

	timerAnimation_ = 0;
	width_ = height_ = 20;
	time_ = 300;
	maxY_ = 0;
	maxX_ = 40;

	textureRect = { 0, 0, width_, height_ };
}

Target::~Target()
{
	missionsPanel_ = nullptr;
	animationManager = nullptr;
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
			if (name_ == "Hipo") {
				game->newDialogue("HipoWaitingPackage");
			}
			else if (name_ == "Frog") {
				game->newDialogue("FrogWaitingPackage");
			}else if (name_ == "Fish")
				game->newDialogue("FishWaitingPackage");
		}
	}
}

void Target::draw() {
	if (active_) {
		
		 SDL_Rect pos = getCollider();

        //Dibujamos respecto a la camara
        pos.x -= (int)game->getCamera()->getCameraPosition().getX();
        pos.y -= (int)game->getCamera()->getCameraPosition().getY();

		animationManager->getFrameImage(pos, textureRect, texture, timerAnimation_, flip, width_, height_, maxX_, maxY_, time_);
	}
}

void Target::setTexture(string tex)
{
	if (tex == "NPC_Tucan") {
		texture = game->getTexture(npc_Tucan);
		name_ = "Tucan";

	}else if (tex == "NPC_Coco") {
		texture = game->getTexture(npc_Coco);
		name_ = "Coco";

	}else if (tex == "NPC_Eagle") {
		texture = game->getTexture(npc_Eagle);
		name_ = "Eagle";

	}else if (tex == "NPC_Fish") {
		texture = game->getTexture(npc_Fish);
		name_ = "Fish";

	}else if (tex == "NPC_Fox") {
		texture = game->getTexture(npc_Fox);
		name_ = "Fox";

	}else if (tex == "NPC_Frog") {
		texture = game->getTexture(npc_Frog);
		name_ = "Frog";

	}else if (tex == "NPC_Hipo") {
		texture = game->getTexture(npc_Hipo);
		name_ = "Hipo";

	}else if (tex == "NPC_Pavo") {
		texture = game->getTexture(npc_Pavo);
		name_ = "Pavo";

	}else if (tex == "NPC_Rabbit") {
		texture = game->getTexture(npc_Rabbit);
		name_ = "Rabbit";

	}
}