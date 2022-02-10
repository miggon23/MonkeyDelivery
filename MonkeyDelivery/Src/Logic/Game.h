//
// Created by espeto on 20/8/45.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>

#include"../Control/States/StateMachine.h"
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

using namespace std;

class Game : public StateMachine {

private:
    string name;
    bool doExit;
    int width, height;

    TextureContainer* textureContainer;
    SDL_Renderer* renderer = nullptr;

public:
  

    Game(string name, int width, int height);
    ~Game();

    string getGameName();

    void setUserExit();
    bool isUserExit();


    int getWindowWidth();
    int getWindowHeight();

    // rendering
    void setRenderer(SDL_Renderer* renderer);
    void loadTextures();
    Texture* getTexture(TextureName name);
    SDL_Renderer* getRenderer();
};



