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
    for (auto enemy : enemyContainer_)
        delete enemy;

    gameObjects_.clear();
    enemyContainer_.clear();
    cout << "[DEBUG] deleting game" << endl;
    delete player_;
    delete textureContainer_;
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
    player_ = new Player(this); //Creacion del jugador
   
    iE_ = new InteractiveEntity(this, tucanTexture, 500, 80);
    add(iE_);

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_); 

    enemiesCreation();//creacion de enemigos
    

    missions_ = new MissionManager(this);

    info = new UI_Info(this);
    auto* x = new Bed(this);
    x->setPosition(500, 300);
    add(x);
    //missions_->AddMission(new Mission(missions_, missionsPanel_, 500, 100, 150, 15, "PruebaMision"));

}

void Game::update()
{
    player_->update();
    //cat_->update();

    for (auto gO : gameObjects_) {
        gO->update();
    }
    for (auto enemy : enemyContainer_)
        enemy->update();
    
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
    for (auto enemy : enemyContainer_)
        enemy->draw();

    player_->draw();
    info->draw();

    missionsPanel_->draw();
    //renderText("aaaa", 100, 150, BLACK);
}
Point2D<int> Game::getOrigin() {
    return { int(-(player_->getX() - player_->getWidth())), 0 };
}

int Game::getWindowWidth() {
    return width;
}

int Game::getWindowHeight() {
    return height;
}

void Game::useInventory(int slot)
{
    player_->useObject(slot);
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer_ = new TextureContainer(renderer);
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer_->getTexture(name);
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
   return player_->moneyChange(money);
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
    return iE_;
}
void Game::addEnemies(Enemy* enemy)
{
    enemyContainer_.push_back(enemy);
}
void Game::enemiesCreation()
{
    bat_ = new Bat(this, 20, Point2D<int>(200, 80), 7);
    cat_ = new Cat(this, 50, getOrigin());
    addEnemies(bat_);
    addEnemies(cat_);
}


