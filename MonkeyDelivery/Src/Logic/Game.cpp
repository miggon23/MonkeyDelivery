#include "Game.h" 

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false)
{    
    font_ = new Font("../Images/TheMoon.ttf", 50);
    
}

Game::~Game() {
    //usar iteradores
    for (auto gO : gameObjects_)
    {
        delete gO;
    }
    gameObjects_.clear();
    cout << "[DEBUG] deleting game" << endl;
    delete player;
    delete textureContainer;
    delete missions_;
    delete font_;
    delete info;
    //delete missionsPanel_; solo poner si no va en el vector de gameobjects
}

string Game::getGameName() {
    return name;
}

void Game::add(GameObject* gameObject) {//a�adir gO al vector
    gameObjects_.push_back(gameObject);
}

void Game::start()
{
    player = new Player(this); //Creacion del jugador

    iE = new InteractiveEntity(this, tucanTexture, 500, 80);
    add(iE);

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_); 

    missions_ = new MissionManager(this);

    info = new UI_Info(this);
    Enemy* e = new Enemy(this, 20, Point2D<int>(200, 80));
    e->addCheckPoint(Point2D<double>(275, 80));
    e->addCheckPoint(Point2D<double>(400, 50));
    add(e);
   
    //missions_->AddMission(new Mission(missions_, missionsPanel_, 500, 100, 150, 15, "PruebaMision"));

}

void Game::update()
{
    player->update();

    for (auto gO : gameObjects_) {
        gO->update();
    }
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

void Game::draw()
{
   /* gameObjects_[0]->draw();
    gameObjects_[1]->draw();*/
    for (auto gO : gameObjects_) {
        gO->draw();
    }
    player->draw();
    info->draw();

    missionsPanel_->draw();
    //renderText("aaaa", 100, 150, BLACK);
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

void Game::useInventory(int slot)
{
    player->useObject(slot);
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
//modifica el dinero del jugador y devulve bool de confirmaci�n en caso de compra
//actua como enlace al m�todo del jugador
bool Game::changeMoneyPlayer(int money)
{
   return player->moneyChange(money);
}

//al pulsar el bot�n de interactuar(space), se relizan los cambios necesarios
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
        // gameObjects_[i]->isInteractive() quitar�a esto del if
        if(gameObjects_[i]->collide(rect)){
            interactEnt.push_back(gameObjects_[i]);
        }
    }
    
    return interactEnt;
}
// M�todo que recibe una misi�n para declararla como la actual
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
