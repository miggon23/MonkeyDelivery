#include "TutorialBook.h"
#include "../Logic/Game.h"
#include "DialogueBox.h"
#include "../json/JSON.h"

TutorialBook::TutorialBook(Game* game, int x, int y, int w, int h) : GameObject(game, true) {
	setTexture(bookTexture);
	setDimension(w, h);
	setPosition(x, y);
	//MissionsPanel::loadMissions("../Images/config/resources.json");
	//setText("pachuco");
}

void TutorialBook::onPlayerInteraction(Player* player)
{
	active = !active;
	if (active) {
		cout << "Interaccion libro tutorial asie asie" << endl;
		string a = "Tutorial";
		game->newDialogue(a);
	}
}
void TutorialBook::draw()
{
	drawTexture(texture);
	// drawDebug();
}

bool TutorialBook::collide(SDL_Rect other) {
	auto c = this->getCollider();
	return (SDL_HasIntersection(&c, &other));
}

bool TutorialBook::isInteractive() {
	return true;
}