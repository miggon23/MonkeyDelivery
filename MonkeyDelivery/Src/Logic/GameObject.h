#ifndef MONKEYDELIVERY_GAMEOBJECT_H
#define MONKEYDELIVERY_GAMEOBJECT_H

#include "../View/TextureContainer.h"
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
    Game* game;

    Texture* texture;

    void drawTexture(Texture* texture);
public:
    void setTexture(TextureName textureName);

    GameObject(Game* game, bool rel = false) : game(game), relative_(rel) {
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