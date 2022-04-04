//
// Created by espeto on 20/8/45.
//

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
#include "InteractuableChest.h"
#include "MissionsPanel.h"

#include "AnimationManager.h"

#include "Shop.h"

#include "./tmxlite/Map.hpp"
#include "./tmxlite/Layer.hpp"
#include "./tmxlite/TileLayer.hpp"
#include "./tmxlite/ObjectGroup.hpp"
#include "./tmxlite/Tileset.hpp"

#include "../View/Camera.h"
#include "../utils/Vector2D.h"

#include "../json/JSON.h"
#include "../sdlutils/SDLUtils.h"

#define TILE_SIZE 16

using uint = unsigned int;
using tileset_map = std::map<std::string, Texture*>;

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
class Brightness;
using namespace std;
class Game : public StateMachine {

private:
    SDL_Texture* background_;
    MapInfo mapInfo;
    tileset_map tilesets_; // textures map (string -> texture)
    void loadSpriteSheets();
    float MAPSCALE_ = 0.3;

    Camera* mCamera_;
    const float LERPVALUE_ = 0.2f;
    void setCamera();
    SDL_Rect srcRect_;
    SDL_Window* window_;
    const Vector2D<float> CAMINITPOSITION_ = { 200.0,50.0 };

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

    //Tienda    
    Shop* shop_;

    //Sounds&Music
    int musicVolume_ = 64;
    int soundEfectsVolume_ = 64;
    int generalVolume_ = 64;
    //Brightness
    Brightness* brightness_=nullptr;

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

    //Player
    inline void move(pair<double, double> speed) { player_->move(speed); };
    inline void setIsRunning(bool run) { player_->setIsRunning(run); };
    inline void setVel(double x) { player_->setVel(x); };
    inline void setPlayerDirX(int x) { player_->setDirX(x); };
    inline void setPlayerDirY(int y) { player_->setDirY(y); };
    inline Point2D<double> getPosisitionPlayer() { return player_->getPosition(); };
    void useInventory(int slot);
    inline void drainPlayerEnergy(float amount) { player_->drainEnergy(amount); };

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
    inline void newDialogue(const string& text) { dialogueBox_->changeText(text); };
   
    //Tilemap
    void loadMap(string const& filename);

    // Camara
    inline void setWindow(SDL_Window* w) { window_ = w; };
    inline Camera* getCamera() { return mCamera_; };  
    void actualiceCameraPos();
    const Point2D<float> getCurrentCenter();
    const Point2D<float> getCurrentMove();
    inline Point2D<float> getSizeMap() 
    { return Point2D<float>{ (float)(mapInfo.tile_width * mapInfo.cols) , (float)(mapInfo.tile_height * mapInfo.rows) }; }
    inline float getMapScale() {
        return MAPSCALE_;
    };
      
    float x;
    float y;

    //Tienda
    Shop* getShop() { return shop_; }

    //Sounds&Music
    inline void ChangeMusicVolume(int volume) { musicVolume_ = volume;/* std::cout << musicVolume_ << std::endl;*/ };
    inline void ChangeSoundEfectsVolume(int volume) { soundEfectsVolume_ = volume; /*std::cout << soundEfectsVolume_ << std::endl;*/};
    inline void ChangeGeneralVolume(int volume) { generalVolume_ = volume; /*std::cout << generalVolume_ << std::endl;*/};

    //Brightness
    void DrawBrightness();
    void ChangeAlphaBrightness(Uint8 x);
    void initBrightness();
};