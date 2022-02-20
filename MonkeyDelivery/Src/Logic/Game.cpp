#include "Game.h"

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false)
{    
    font_ = new Font("../Images/Monospace.ttf", 12);
}

Game::~Game() {
    cout << "[DEBUG] deleting game" << endl;
    delete player;
    delete iE;
    delete textureContainer;
    delete missions_;
    delete font_;
}

string Game::getGameName() {
    return name;
}

void Game::start()
{

    player = new Player(this); //Creacion del jugador
    iE = new InteractiveEntity(this);

    missions_ = new MissionManager(this);
    missions_->AddMission(new Mission(missions_, iE, 100, 100, 10));
}

void Game::update()
{
    player->update();
    iE->update();
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

void Game::draw()
{
    player->draw();
    iE->draw();
   

}
Point2D<int> Game::getOrigin() {
    return { int(-(player->getX() - player->getWidth())), 0 };
}

int Game::getWindowWidth() {
    return width;
}

int Game::getWindowHeight() {
    return height;
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer = new TextureContainer(renderer);
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer->getTexture(name);
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

void Game::renderText(string text, int x, int y, SDL_Color color)
{
    font_->render(renderer, text.c_str(), x, y, color);
}

void Game::renderText(vector<string> text, int x, int y, int incX, int incY, SDL_Color color)
{
    for (int i = 0; i < text.size(); ++i) {
        font_->render(renderer, text[i].c_str(), x, y, color);
        x += incX;
        y += incY;
    }
}

//economy
//modifica el dinero del jugador y devulve bool de confirmación en caso de compra
//actua como enlace al método del jugador
bool Game::changeMoneyPlayer(int money)
{
   return player->moneyChange(money);
}

//al pulsar el botón de interactuar(space), se relizan los cambios necesarios
void Game::interactions()
{
    missions_->checkCurrentMission();
}

//adri y simona: colisiones
vector<GameObject*> Game::getCollisions(SDL_Rect rect)
{
    vector<GameObject*>interactEnt;
    //for (int i = 0; i < interactEnt.size(); i++)
    //{
    //    if(interactEnt[i]->collide())
    //}
    //return interactEnt;
    if(iE->collide(rect)){
        interactEnt.push_back(iE);
    }
    return interactEnt;
};
