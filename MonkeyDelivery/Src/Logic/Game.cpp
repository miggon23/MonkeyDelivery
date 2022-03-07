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
    delete font_;
    delete info;  
    //delete missionsPanel_; solo poner si no va en el vector de gameobjects
    delete dialogueBox_;
    delete iE_;
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
   
   

    //iE_ = new InteractiveEntity(this, tucanTexture, 500, 80);
    //add(iE_);

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_); 

    enemiesCreation();//creacion de enemigos
    

    //missions_ = new MissionManager(this);

    dialogueBox_ = new DialogueBox(this);
    dialogueBox_->changeText("DialogueBox1");
    dialogueBox_->show();

    info = new UI_Info(this);
    auto* x = new Bed(this);
    x->setPosition(500, 300);
    add(x);
}

void Game::update()
{
    player_->update();

    for (auto gO : gameObjects_)
        gO->update();
    

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
    for (auto gO : gameObjects_) 
        gO->draw();
    
    for (auto enemy : enemyContainer_)
        enemy->draw();

    info->draw();

    missionsPanel_->draw();

    dialogueBox_->draw();
    //renderText("aaaa", 100, 150, BLACK);
    
    player_->draw();
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
   // addEnemies(new Cat(this, 50, Point2D<int>(100, 100)));
   // addEnemies(new Bat(this, 20, Point2D<int>(200, 80), 7));
    addEnemies(new Bull(this, 35, Point2D<int>(350, 70)));
}

void Game::scare(double scariness)
{
    player_->getScared(scariness);
}


