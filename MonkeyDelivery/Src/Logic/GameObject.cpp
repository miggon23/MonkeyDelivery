#include "GameObject.h"
#include "../Logic/Game.h"

void GameObject::drawTexture(Texture* texture) {
    int dX =/* game->getOrigin().*/getX();
    int dY = /*game->getOrigin().*/getY();

    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x , c.y , c.w, c.h };
    texture->render(textureBox);
}

void GameObject::setTexture(TextureName textureName)
{
    this->texture = game->getTexture(textureName);
}

void GameObject::drawDebug()
{
    SDL_Rect c = { getX(), getY(),
         getWidth(), getHeight() };
    Box(c, RED).render(game->getRenderer());
    //Box(getCenter(), BLUE).render(game->getRenderer());
}

SDL_Rect GameObject::getCollider() {
    return { int(getX()),
             int(getY()),
             getWidth(),
             getHeight() };
}

SDL_Rect GameObject::getCenter()
{
    return { int(getX()) + game->getOrigin().getX(),
            int(getY()) + game->getOrigin().getY() ,
            10, 10 };
}


void GameObject::setPosition(double x, double y)
{
    
    position_= Point2D<double>(x, y);
}

void GameObject::setDimension(double width, double height)
{
    w = width;
    h = height;
}

void GameObject::draw()
{
    drawTexture(texture);
    cout << "simio";
}

bool GameObject::collide(SDL_Rect other) {
    // DEBERÍA FUNCIONAR Y NO FUNCIONA
    //return SDL_HasIntersection(&getCollider(), &other);
    return false;
}