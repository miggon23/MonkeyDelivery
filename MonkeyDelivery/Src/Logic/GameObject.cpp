#include "GameObject.h"
#include "../Logic/Game.h"

void GameObject::drawTexture(Texture* texture) {
    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();

    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h };
    texture->render(textureBox);
}
void GameObject::setTexture(TextureName textureName)
{
    this->texture = game->getTexture(textureName);
}

SDL_Rect GameObject::getCollider() {
    return { int(getX() - getWidth() / 2),
             int(getY() - getHeight() / 2),
             getWidth(),
             getHeight() };
}


void GameObject::draw()
{
    drawTexture(texture);
    cout << "simio";
}

