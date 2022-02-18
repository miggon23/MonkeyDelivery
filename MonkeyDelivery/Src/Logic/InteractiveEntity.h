#pragma once
#include "GameObject.h"




class InteractiveEntity:public GameObject {


public:

    InteractiveEntity(Game* game) : GameObject(game) {

    };
    
    virtual void update();

    bool collide(SDL_Rect other);
  
};
