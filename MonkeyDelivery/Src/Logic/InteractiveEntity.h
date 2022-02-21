#pragma once
#include "GameObject.h"




class InteractiveEntity:public GameObject {


public:

    InteractiveEntity(Game* game, TextureName textureName, int position);
    
    virtual void update();
    void draw() override;

    bool collide(SDL_Rect other);

    bool isInteractive();
  
};
