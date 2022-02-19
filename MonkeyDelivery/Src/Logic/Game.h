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
#include "Player.h"
#include "InteractiveEntity.h"
#include "Mission.h"
#include "MissionManager.h"

using namespace std;

class Game : public StateMachine {

private:
    string name;
    bool doExit;
    int width, height;

    TextureContainer* textureContainer;
    SDL_Renderer* renderer = nullptr;
    Player* player = nullptr;
    InteractiveEntity* iE = nullptr;
    MissionManager* missions_ = nullptr;
    

public:
  

    Game(string name, int width, int height);
    ~Game();

    string getGameName();

    void start();
    void update();

    void setUserExit();
    bool isUserExit();
    void draw();
    Point2D<int> getOrigin();
    int getWindowWidth();
    int getWindowHeight();

    void move(pair<double, double> speed) { player->move(speed); };

    // rendering
    void setRenderer(SDL_Renderer* renderer);
    void loadTextures();
    Texture* getTexture(TextureName name);
    SDL_Renderer* getRenderer();
    Player* getPlayer() {
        return player;
    }

    // missions
    bool changeMoneyPlayer(int money);
    void interactions();
};



