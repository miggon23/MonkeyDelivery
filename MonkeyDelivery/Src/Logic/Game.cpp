#include "Game.h" 

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false)
{    
    font_ = new Font("../Images/TheMoon.ttf", 50);
    
}

Game::~Game() {
    
    for (int i = 0; i < gameObjects_.size(); i++)
    {
        delete gameObjects_[i];
    }
    gameObjects_.clear();
    cout << "[DEBUG] deleting game" << endl;
    delete player;
    delete iE;
    delete textureContainer;
    delete missions_;
    delete font_;
    delete info;
}

string Game::getGameName() {
    return name;
}

void Game::add(GameObject* gameObject) {//añadir gO al vector
    gameObjects_.push_back(gameObject);
}

void Game::start()
{
    player = new Player(this); //Creacion del jugador

    iE = new InteractiveEntity(this, tucanTexture, 600);
    //add(iE);

    missionsPanel_ = new InteractiveEntity(this, woodPanel, 200);
    add(missionsPanel_);

    missions_ = new MissionManager(this);

    info = new UI_Info(this);

    missions_->AddMission(new Mission(missions_, missionsPanel_, 500, 100, 150, 15, "PruebaMision"));

}

void Game::update()
{
    player->update();
    gameObjects_[0]->update();
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
    gameObjects_[0]->draw();
    //renderText("aaaa", 100, 150, BLACK);
    info->draw();
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
    
    // for que recorre el vector de gameobjects
    for (int i = 0; i < gameObjects_.size(); i++)
    {
        if(gameObjects_[i]->isInteractive() && gameObjects_[i]->collide(rect)){
            interactEnt.push_back(gameObjects_[i]);
        }
    }
    
    return interactEnt;
}
// Método que recibe una misión para declararla como la actual
// Se llama cuando se selecciona desde SelectMissionCommand
void Game::setActiveMission(Mission* m)
{
    missions_->AddMission(m);
}

// devuelve la iE 
InteractiveEntity* Game::getiE()
{
    return iE;
}
;
