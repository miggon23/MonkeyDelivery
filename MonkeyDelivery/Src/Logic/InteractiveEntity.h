#pragma once
#include "GameObject.h"




class InteractiveEntity:public GameObject {


public:

    InteractiveEntity(Game* game, TextureName textureName, int positionX, int positionY);
    
    virtual void update();
    void draw() override;

    bool collide(SDL_Rect other);

    bool isInteractive();
  
};
