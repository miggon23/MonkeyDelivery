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

#include "../View/Font.h"

#include "Player.h"
#include "InteractiveEntity.h"

#include "Mission.h"
#include "MissionManager.h"
#include "UI_Info.h"
#include "Inventory.h"

#include "Enemy.h"

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
    vector<GameObject*> gameObjects_;
    
    GameObject* missionsPanel_= nullptr;

    Font* font_;
    UI_Info* info;

public:

    Game(string name, int width, int height);
    ~Game();

    string getGameName();

    void add(GameObject* gameObject);

    void start();
    void update();

    void setUserExit();
    bool isUserExit();
    void draw();
    Point2D<int> getOrigin();
    int getWindowWidth();
    int getWindowHeight();

    //Player movement
    inline void move(pair<double, double> speed) { player->move(speed); };
    inline void setIsRunning(bool run) { player->setIsRunning(run); };
    inline void setVelX(double x) { player->setVelX(x); };
    inline void setVelY(double y) { player->setVelY(y); };
    inline void setPlayerDirX(int x) { player->setDirX(x); };
    inline void setPlayerDirY(int y) { player->setDirY(y); };
    void useInventory(int slot);

    // rendering
    void setRenderer(SDL_Renderer* renderer);
    void loadTextures();
    Texture* getTexture(TextureName name);
    SDL_Renderer* getRenderer();
    inline Player* getPlayer() { return player; }
    inline MissionManager* getMissionManager() { return missions_; }
    void renderText(string text, int x, int y, SDL_Color color = { 0,0,0 }); // Escribir una sola línea
    void renderText(vector<string> text, int x, int y, int incX, int incY, SDL_Color color = { 0,0,0 }); // Escribir varias líneas

    // missions
    bool changeMoneyPlayer(int money);
    void interactions();
    vector<GameObject*>getCollisions(SDL_Rect rect);
    void setActiveMission(Mission* m);
    InteractiveEntity* getiE();

};



