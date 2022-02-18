#include "InteractiveEntity.h"
#include "../Logic/Game.h"


bool InteractiveEntity::collide(SDL_Rect other) {
    // DEBERÍA FUNCIONAR Y NO FUNCIONA
    //return SDL_HasIntersection(&getCollider(), &other);
    return false;
}