#pragma once
#include "GameObject.h"

class TutorialBook:public GameObject {

    bool active = false;
    string textPath_;
public:

    TutorialBook(Game* game, int x, int y, int w, int h);
    
    void onPlayerInteraction(Player* player) override;
    void draw() override;
    void update() override{}
    bool collide(SDL_Rect other);

    bool isInteractive();
    inline void setText(const string& textName) {
        textPath_ = textName + "Text";
    };
};