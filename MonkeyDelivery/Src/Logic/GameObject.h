#ifndef MONKEYDELIVERY_GAMEOBJECT_H
#define MONKEYDELIVERY_GAMEOBJECT_H

// TODO: add includes
//#include "../Game.h"

//#include "../../Utils/Vector2D.h"
//#include "../../View/Texture.h"
//#include "../../View/Box.h"
//#include "../../View/TextureContainer.h"
#include "../View/TextureContainer.h"
#include "../View/Texture.h"


class Game;

class GameObject {

   

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

    virtual void draw();
    virtual void update() = 0;

    virtual SDL_Rect getCollider();

  
};
#endif 