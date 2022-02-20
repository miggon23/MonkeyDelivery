#ifndef MONKEYDELIVERY_GAMEOBJECT_H
#define MONKEYDELIVERY_GAMEOBJECT_H

#include "../View/TextureContainer.h"
#include "../View/Texture.h"
#include "../Utils/Vector2D.h"
#include "../View/Box.h"


class Game;

class GameObject {

    Point2D<double> position_;
    int w = 20, h = 20;

protected:
    Game* game;
    Texture* texture;

    void drawTexture(Texture* texture);
    void setTexture(TextureName textureName);
public:

    GameObject(Game* game) : game(game) {

    };
    virtual ~GameObject() {
        game = nullptr;
        texture = nullptr;
    };
    int getX() { return position_.getX(); };
    int getY() { return position_.getY(); };
    void setPosition(double x, double y);
    Point2D<double> getPosition() { return position_; }
    void setDimension(double width, double height);
    int getWidth() { return w; };
    int getHeight() { return h; };
    virtual void draw();
    virtual void update() = 0;

    void drawDebug();

    virtual SDL_Rect getCollider();
    SDL_Rect getCenter();
    bool collide(SDL_Rect other);
    void exampleInter();
};
#endif 