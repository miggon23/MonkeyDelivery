#include "../Logic/Game.h"

TutorialBook::TutorialBook(Game* game, int x, int y, int w, int h) : ColliderTile(game, Point2D<double>(x,y), w, h) {
	setTexture(worldObject_Tutorial);
	tutorialTexture_ = game->getTexture(UI_Controls);
	tutorialRect_ = {0, 0, (int)game->getWindowWidth(), (int)game->getWindowHeight() };
}

void TutorialBook::onPlayerInteraction(Player* player)
{
	isActive_ = false;
	isColliding_ = false;
	onPlayerCollisionExit();

	showingImage_ = !showingImage_;
	player->changeTalking(showingImage_);
}

void TutorialBook::draw()
{
	drawTexture(texture);

	if (showingImage_) {
		tutorialTexture_->render(tutorialRect_);
	}
}

bool TutorialBook::isInteractive() {
	return true;
}