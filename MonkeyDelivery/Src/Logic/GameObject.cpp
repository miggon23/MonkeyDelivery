#include "GameObject.h"
#include "../Logic/Game.h"

#include "../Control/States/MissionSelectionState.h"

void GameObject::drawTexture(Texture* texture) {

    if (!relative_)
    {
        SDL_Rect c = getCollider();
        SDL_Rect textureBox = { c.x , c.y , c.w, c.h };
        texture->render(textureBox);
    }
    else
    {
        SDL_Rect pos = getCollider();

        //Dibujamos respecto al centro de la camara
        //Recordemos que el getCameraPosition nos devuelve el x e y del rect (Arriba a la izquierda de la cámara
        //pos.x -= (game->getCamera()->getCameraPosition().getX() / game->getCamera()->getWidth());
        //pos.y -= (game->getCamera()->getCameraPosition().getY() / game->getCamera()->getHeight());

        pos.x -= (game->getCamera()->getCameraPosition().getX() - game->getWindowWidth() / 2);
        pos.y -= (game->getCamera()->getCameraPosition().getY() - game->getWindowHeight() / 2);

        texture->render(pos);
    };
}

void GameObject::setTexture(TextureName textureName)
{
    this->texture = game->getTexture(textureName);
}

void GameObject::drawDebug()
{
    SDL_Rect c = { getX(), getY(),
         getWidth(), getHeight() };

    //c.x -= (game->getCamera()->getCameraPosition().getX() - game->getCamera()->getWidth()) / game->getMapScale();
    //c.y -= (game->getCamera()->getCameraPosition().getY() - game->getCamera()->getHeight()) / game->getMapScale();
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
    return { int(getX()),
            int(getY()),
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
}

bool GameObject::collide(SDL_Rect other) {
    auto c = getCollider();
    return SDL_HasIntersection(&c, &other);
}

// adri y simona: metodo de ejemplo para el interactive
// no tocar ;)
void GameObject::exampleInter(Player* player)
{
   // cout << "ejemplo" << endl;
    onPlayerInteraction(player);
}
