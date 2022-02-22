#include "InteractiveEntity.h"
#include "../Logic/Game.h"

InteractiveEntity::InteractiveEntity(Game* game, TextureName textureName, int positionX, int positionY) : GameObject(game) {
    this->game = game;
    texture = nullptr;
    setTexture(textureName);

    setPosition(positionX, positionY);
    setDimension(120, 150);
}

void InteractiveEntity::update()
{
    if (collide(game->getPlayer()->getCollider()));
       // cout<<"COLLISION"<<endl;
        
}

void InteractiveEntity::draw()
{
    drawTexture(texture);
   // drawDebug();
}

bool InteractiveEntity::collide(SDL_Rect other) {
    auto c = this->getCollider();
    return (SDL_HasIntersection(&c, &other));
}

bool InteractiveEntity::isInteractive() {
    return true;
}