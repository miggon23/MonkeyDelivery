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

#include "Bat.h"
#include "Cat.h"
#include "Bull.h"

#include "Bed.h"

#include "MissionsPanel.h"

using namespace std;

class Game : public StateMachine {

private:
    string name;
    bool doExit;
    int width, height;   

    TextureContainer* textureContainer_;
    SDL_Renderer* renderer = nullptr;
    Player* player_ = nullptr;
    InteractiveEntity* iE_ = nullptr;
    vector<GameObject*> gameObjects_;
    vector<Enemy*>enemyContainer_;//vector enemigos
    
    MissionsPanel* missionsPanel_= nullptr;
    

    Font* font_;
    UI_Info* info;

    //prueba cuadro dialogo
    DialogueBox* dialogueBox_;
    

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
    inline void move(pair<double, double> speed) { player_->move(speed); };
    inline void setIsRunning(bool run) { player_->setIsRunning(run); };
    inline void setVelX(double x) { player_->setVelX(x); };
    inline void setVelY(double y) { player_->setVelY(y); };
    inline void setPlayerDirX(int x) { player_->setDirX(x); };
    inline void setPlayerDirY(int y) { player_->setDirY(y); };
    inline Point2D<double> getPosisitionPlayer() { return player_->getPosition(); };
    void useInventory(int slot);

    // rendering
    void setRenderer(SDL_Renderer* renderer);
    void loadTextures();
    Texture* getTexture(TextureName name);
    SDL_Renderer* getRenderer();
    inline Player* getPlayer() { return player_; }
   // inline MissionManager* getMissionManager() { return missions_; }
    void renderText(string text, int x, int y, SDL_Color color = { 0,0,0 }); // Escribir una sola l�nea
    void renderText(vector<string> text, int x, int y, int incX, int incY, SDL_Color color = { 0,0,0 }); // Escribir varias l�neas

    // missions
    bool changeMoneyPlayer(int money);
    vector<GameObject*>getCollisions(SDL_Rect rect);
    void setActiveMission(Mission* m);
    InteractiveEntity* getiE();
    inline MissionsPanel* getMissionsPanel() { return missionsPanel_; };

    //enemies
    void addEnemies(Enemy* enemy);//añade enemigos al vector
    void enemiesCreation();//llama al addenemy con cada enemigo que queremos añadir, se llama en start
    void scare(double scariness);
   
};



