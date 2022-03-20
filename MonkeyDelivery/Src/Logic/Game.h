//
// Created by espeto on 20/8/45.
//

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../TilemapSrc/tileObject.h"

#include"../Control/States/StateMachine.h"
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

#include "../View/Font.h"

#include "Player.h"
#include "InteractiveEntity.h"

#include "Mission.h"
#include "DialogueBox.h"
#include "UI_Info.h"
#include "Inventory.h"

#include "Enemy.h"

#include "Bat.h"
#include "Cat.h"
#include "Bull.h"
#include "Scorpion.h"
#include "Plant.h"

#include "Bed.h"
#include "InteractuableShop.h"
#include "MissionsPanel.h"

#include "AnimationManager.h"

#include "Shop.h"

#include "./tmxlite/Map.hpp"
#include "./tmxlite/Layer.hpp"
#include "./tmxlite/TileLayer.hpp"
#include "./tmxlite/ObjectGroup.hpp"
#include "./tmxlite/Tileset.hpp"

#define TILE_SIZE 16

using uint = unsigned int;

struct MapInfo{
    tmx::Map* tile_map;
    string path;
    int rows, cols;
    int tile_width, tile_height;
    map<uint, Texture*> tilesets;

    MapInfo() {
        tile_map = nullptr;
        path = "";
        rows = cols = tile_width = tile_height = 0;
    }
    ~MapInfo() {
        if (tile_map != nullptr)
            delete tile_map;
    }
};

using namespace std;
class Game : public StateMachine {

private:

    MapInfo mapInfo;

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
    
    AnimationManager* animationManager;

    Font* font_;
    UI_Info* info;

    //prueba cuadro dialogo
    DialogueBox* dialogueBox_;
    
    //TILEMAP
    vector<tileObject> map;

    //Tienda    
    Shop* shop_;

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
    inline void setVel(double x) { player_->setVel(x); };
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
    InteractiveEntity* getiE();
    inline MissionsPanel* getMissionsPanel() { return missionsPanel_; };

    //enemies
    void addEnemies(Enemy* enemy);//añade enemigos al vector
    void enemiesCreation();//llama al addenemy con cada enemigo que queremos añadir, se llama en start
    void scare(double scariness);

    //texts
    void interactDialogue();
   
    //Tilemap
    void loadMap(string const& filename);
    void drawMap();
    void drawTiles(tileObject o);

    //Tienda
    Shop* getShop() { return shop_; }
};