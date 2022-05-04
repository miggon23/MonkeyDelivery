#ifndef MONKEYDELIVERY_GAMEOBJECT_H
#define MONKEYDELIVERY_GAMEOBJECT_H

#include "../View/TextureContainer.h"
#include "./AnimationManager.h"
#include "../View/Texture.h"
#include "../utils/Vector2D.h"
#include "../View/Box.h"


class Game;
class Player; // para hacer onPlayerCollision

class GameObject {

    Point2D<double> position_;
    int w = 20, h = 20;
    bool relative_; // Si tiene que dibujarse relativo al mapa o no -> por defecto a false

protected:
    AnimationManager* animationManager;

    Game* game;

    Texture* texture;
    SDL_RendererFlip flip;
    SDL_Rect textureRect;
    int width_;
    int height_;
    int maxX_;
    int maxY_;
    int time_;
    float timerAnimation_; //tiempo entre los frames

    void drawTexture(Texture* texture);
public:
    void setTexture(TextureName textureName);
    inline void setFlip(SDL_RendererFlip f) { flip = f; }

    GameObject(Game* game,  bool rel = false) : game(game), relative_(rel), texture(nullptr), flip(SDL_FLIP_NONE), animationManager(AnimationManager::Instance()),
        height_(),maxX_(),maxY_(),textureRect(),timerAnimation_(),time_(),width_() {
    };
    virtual ~GameObject() {
        game = nullptr;
        texture = nullptr;
    };
    int getX() { return (int)position_.getX(); };
    int getY() { return (int)position_.getY(); };
    void setPosition(double x, double y);
    Point2D<double> getPosition() { return position_; }
    void setDimension(double width, double height);
    int getWidth() { return w; };
    int getHeight() { return h; };
    virtual void draw();
    virtual void update() = 0;
    // adri y simona: pasa distinguir entre interactuables
    virtual bool isInteractive() { return false; };

    void drawDebug();

    virtual SDL_Rect getCollider();
    SDL_Rect getCenter();
    bool collide(SDL_Rect other);
    void exampleInter(Player* player);

    // INTERACCIONES
    virtual void onPlayerInteraction(Player* player) {};
  
};
#endif 