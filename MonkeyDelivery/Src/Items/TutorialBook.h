#pragma once
#include "../Logic/ColliderTile.h"

class TutorialBook : public ColliderTile {

    bool showingImage_ = false;
    Texture* tutorialTexture_;
    SDL_Rect tutorialRect_;
    SDL_Rect tutorialSignRect_;

public:

    TutorialBook(Game* game, int x, int y, int w, int h);
    
    void onPlayerInteraction(Player* player) override;
    void draw() override;

    bool isInteractive();
};