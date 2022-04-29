#include "Game.h"
#include "../Control/States/OptionsState.h"
#include "GameObjectGenerator.h"
#include <cmath>


void Game::updateCameraPos()
{
    Vector2D<double> v = { round(player_->getPosition().getX() - getWindowWidth() / 2), round(player_->getPosition().getY() - getWindowHeight() / 2) };
    mCamera_->setPos(v);
}

Game::Game(string n, double w, double h) : name(n), width(w), height(h), doExit(false), mCamera_(nullptr), mapOpened(false), mapPoint(nullptr), pIcon(nullptr)
{
    SDLUtils::init("Monkey Delivery", 1800, 1000,
        "Images/config/resources.json");

    setRenderer(sdlutils().renderer());

    string path = "Images/map/minimapOverlay.png";
    maptexture = new Texture(getRenderer(), path);
   
    //maptexture = getTexture(Item_Package);
    font_ = new Font("./Images/fonts/Pixellari.ttf", 50);
    moneyFont_ = new Font("./Images/fonts/Pixellari.ttf", 26);

    animationManager_ = new AnimationManager(this);
}

Game::~Game() {
    cout << "[DEBUG] deleting game" << endl;

    for (auto gO : gameObjects_)
        delete gO;
    for (auto enemy : enemyContainer_)
        delete enemy;
    for (auto col : collisions_)
        delete col;
    collisions_.clear();
    gameObjects_.clear();
    enemyContainer_.clear();
    delete iE_;

    delete mCamera_;
    delete player_;
    delete tutorialBook_;

    delete textureContainer_;
    delete animationManager_;
    delete font_;
    delete moneyFont_;

    delete info;
    delete optionsState;
    delete dialogueBox_;
    delete shop_;

    delete mapPoint;
    delete pIcon; pIcon = nullptr;
    delete maptexture; maptexture = nullptr; 

    for (auto a : tilesets_) {
        a.second->free();
        delete a.second;
    }
    for (auto x : savedStates) {
        delete x;
    }

    delete partSystem;

    SDL_SetWindowBrightness(sdlutils().window(), 1);
    delete window_;
}

void Game::add(GameObject* gameObject) {//a�adir gO al vector
    gameObjects_.push_back(gameObject);
}

void Game::removeGameObject(GameObject* gameObject){
    
    //es necesario el for qui pq si no luego antes de llegar al update peta
    for (int i = 0; i < gameObjects_.size(); i++){
        if (gameObjects_[i] == gameObject) {
            gameObjects_.erase(gameObjects_.begin() + i);
            break;
        }
    }
    delete gameObject; gameObject = nullptr;
}

void Game::start()
{
    inGame = true;

    animationManager_ = new AnimationManager(this);
    player_ = new Player(this, animationManager_); //Creacion del jugador

    // Cámara:
    Vector2D<double> vJug = { (player_->getPosition().getX() - width / 2), (player_->getPosition().getY() - height / 2) };
    mCamera_ = new Camera(this, vJug, CAMSIZE_.getX(), CAMSIZE_.getY()); // Tamaño que se ve del mapa -> debe conservar la proporción de la ventana

    mapInfo.path = ".\\Src\\TilemapSrc\\MainMap.tmx";
    loadMap(mapInfo.path);

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_);
    
    mapPoint = new MAPPoint(this);
    pIcon = new PlayerIcon(this);

    add(new IntectuableShop(this, 3700, 1600));
    shop_ = new Shop(player_, this);

    tutorialBook_ = new TutorialBook(this, 4025, 1700, 100, 75);

    GameObjectGenerator::generateLevel(this);

    dialogueBox_ = new DialogueBox(this);

    info = new UI_Info(this);

   /* auto* bed = new Bed(this);
    bed->setPosition(1820, 1560);
    player_->bedPos(1820, 1560);
    add(bed);*/
    //add(new Rock(this,2500,800));
    auto cama = new Bed(this);
    cama->setPosition(3280, 1090);
    player_->bedPos(3650, 1300);
    add(cama);

    partSystem = new ParticleExample();
    partSystem->setRenderer(renderer);             // set the renderer
    partSystem->setPosition(670, 600);             // set the position
    partSystem->setStyle(ParticleExample::SMOKE);  // set the example effects

    scalePlayerIcon();

    sdlutils().musics().at("gamemusic").play(-1);
}

void Game::update()
{
    player_->update();
    updateCameraPos();
   
    for (auto c : collisions_) {
        c->update();
    }
    tutorialBook_->update();

    for (auto gO : gameObjects_) {

        if (gO != nullptr) 
            gO->update();
       /* else {
            gameObjects_.erase()
        }*/
            
    }

    for (auto enemy : enemyContainer_)
        enemy->update();

    sdlutils().musics().at("gamemusic").setMusicVolume(getMusicVolume() * getGeneralVolume());
}

//Normal draw for entities(no Tiles)
void Game::draw()
{
    // Dibujado del mapa
    SDL_Rect dst = { 0, 0, (int)getWindowWidth(), (int)getWindowHeight() };
    SDL_Rect src = { (int)lround(mCamera_->getCameraPosition().getX() / (getWindowWidth() / mCamera_->getWidth())),
                     (int)lround(mCamera_->getCameraPosition().getY() / (getWindowHeight() / mCamera_->getHeight())),
                     (int)lround(mCamera_->getWidth()),
                     (int)lround(mCamera_->getHeight()) };
    SDL_RenderCopy(renderer, background_, &src, &dst);

  
    for (auto gO : gameObjects_) {
        if(gO!=nullptr)
            gO->draw();
    }

    
    for (auto enemy : enemyContainer_)
        enemy->draw();

    // Dibujar colliders
    //for (auto c : collisions_) {
    //    c->drawDebug();
    //}

    info->draw();

    dialogueBox_->draw();

    //partSystem->draw();
    missionsPanel_->draw();

    tutorialBook_->draw();

    if (!mapOpened && !player_->isInTutorial()) drawMap();
    scalePlayerIcon();

    player_->draw();
}

Point2D<int> Game::getOrigin() {
    return { int(-(player_->getX() - player_->getWidth())), 0 };
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

void Game::renderText(string text, int x, int y, SDL_Color color)
{
    font_->render(renderer, text.c_str(), x, y, color);
}
void Game::renderMoney(string text, int x, int y, SDL_Color color)
{
    moneyFont_->render(renderer, text.c_str(), x, y, color);
}

void Game::renderText(vector<string> text, int x, int y, int incX, int incY, SDL_Color color)
{
    for (int i = 0; i < text.size(); ++i) {
        font_->render(renderer, text[i].c_str(), x, y, color);
        x += incX;
        y += incY;
    }
}

void Game::restart()
{
    // comienza a sonar la música de juego de nuevo
    sdlutils().musics().at("gamemusic").play(-1);
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
        if (gameObjects_[i]->collide(rect)) {
            interactEnt.push_back(gameObjects_[i]);
        }
    }
    if (tutorialBook_->collide(rect))
        interactEnt.push_back(tutorialBook_);

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

void Game::scare(double scariness)
{
    player_->getScared((int)scariness);
}

bool Game::interactDialogue()
{
    return dialogueBox_->interact();
}


//TILEMAP
void Game::loadMap(string const& filename)
{
    // Se carga la información del .tmx
    mapInfo.tile_map = new tmx::Map();
    mapInfo.tile_map->load(filename);

    // tamaño del mapa
    auto map_dimensions = mapInfo.tile_map->getTileCount();
    mapInfo.rows = map_dimensions.y;
    mapInfo.cols = map_dimensions.x;

    // tamaño de los tiles
    auto tilesize = mapInfo.tile_map->getTileSize();
    mapInfo.tile_width = tilesize.x;
    mapInfo.tile_height = tilesize.y;

    // convertir a textura
    auto rend = renderer;
    int bgWidth = mapInfo.tile_width * mapInfo.cols;
    int bgHeight = mapInfo.tile_height * mapInfo.rows;
    //SDL_Texture* background_ = SDL_CreateTexture(rend,
    background_ = SDL_CreateTexture(rend,

        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        bgWidth,
        bgHeight
    );
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(background_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, background_);

    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    // (el mapa utiliza el �ndice [gid] del primer tile cargado del tileset como clave)
    // (para poder cargar los tilesets del archivo .tmx, les ponemos de nombre 
    // el nombre del archivo sin extension en el .json) 
    auto& mapTilesets = mapInfo.tile_map->getTilesets();
    for (auto& tileset : mapTilesets) {
        string name = tileset.getName();
        Texture* texture = sdlutils().tilesets().find(name)->second;
        //Texture* texture = tilesets_.find(name)->second;;
        mapInfo.tilesets.insert(pair<uint, Texture*>(tileset.getFirstGID(), texture));
    }
    // recorremos cada una de las capas (de momento solo las de tiles) del mapa
    auto& map_layers = mapInfo.tile_map->getLayers();
    for (auto& layer : map_layers) {
        // aqui comprobamos que sea la capa de tiles
        if (layer->getType() == tmx::Layer::Type::Tile) {
            // cargamos la capa
            tmx::TileLayer* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());

            // obtenemos sus tiles
            auto& layer_tiles = tile_layer->getTiles();

            // recorremos todos los tiles para obtener su informacion
            for (auto y = 0; y < mapInfo.rows; ++y) {
                for (auto x = 0; x < mapInfo.cols; ++x) {
                    // obtenemos el indice relativo del tile en el mapa de tiles
                    auto tile_index = x + (y * mapInfo.cols);

                    // con dicho indice obtenemos el indice del tile dentro de su tileset
                    auto cur_gid = layer_tiles[tile_index].ID;


                    // si es 0 esta vacio asi que continuamos a la siguiente iteracion
                    if (cur_gid == 0)
                        continue;

                    // guardamos el tileset que utiliza este tile (nos quedamos con el tileset cuyo gid sea
                    // el mas cercano, y a la vez menor, al gid del tile)
                    auto tset_gid = -1, tsx_file = 0;;
                    for (auto& ts : mapInfo.tilesets) {
                        if (ts.first <= cur_gid) {
                            tset_gid = ts.first;
                            tsx_file++;
                        }
                        else
                            break;
                    }

                    // si no hay tileset v�lido, continuamos a la siguiente iteracion
                    if (tset_gid == -1)
                        continue;

                    // normalizamos el �ndice
                    cur_gid -= tset_gid;

                    // calculamos dimensiones del tileset
                    auto ts_width = 0;
                    auto ts_height = 0;
                    SDL_QueryTexture(mapInfo.tilesets[tset_gid]->getTexture(),
                        NULL, NULL, &ts_width, &ts_height);

                    // calculamos el area del tileset que corresponde al dibujo del tile
                    auto region_x = (cur_gid % (ts_width / mapInfo.tile_width)) * mapInfo.tile_width;
                    auto region_y = (cur_gid / (ts_width / mapInfo.tile_width)) * mapInfo.tile_height;

                    // calculamos la posicion del tile
                    auto x_pos = x * mapInfo.tile_width;
                    auto y_pos = y * mapInfo.tile_height;

                    // metemos el tile
                    auto tileTex = mapInfo.tilesets[tset_gid];

                    SDL_Rect src;
                    src.x = region_x; src.y = region_y;
                    src.w = mapInfo.tile_width;
                    src.h = mapInfo.tile_height;

                    SDL_Rect dest;
                    dest.x = x_pos;
                    dest.y = y_pos;
                    dest.w = src.w;
                    dest.h = src.h;

                    int tileRot = layer_tiles[tile_index].flipFlags;
                    float rotCorrection = 45;
                    SDL_RendererFlip tileFlip = SDL_FLIP_NONE;
                     
                    //Multiplicamos por 45 porque esta multiplicado por factor de 45 (lo que devuelve rot)
                    mapInfo.tilesets[tset_gid]->render(src, dest, (double) tileRot * rotCorrection, nullptr, tileFlip);
                }
            }
        }

        if (layer->getType() == tmx::Layer::Type::Object) {
            tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());

            auto& objs = object_layer->getObjects();

            for (auto obj : objs) {
                auto rect = obj.getAABB();

                 //   if (obj.getName() == "collision") 

                rect.width *= (float)(getWindowWidth() / mCamera_->getWidth());
                rect.height *= (float)(getWindowHeight() / mCamera_->getHeight());

                rect.left *= (float)(getWindowWidth() / mCamera_->getWidth());
                rect.top *= (float)(getWindowHeight() / mCamera_->getHeight());

                auto a = new ColliderTile(this, Vector2D<double>(rect.left, rect.top), rect.width, rect.height );
                collisions_.push_back(a);
                
            }
        }
    }

    SDL_SetRenderTarget(renderer, nullptr);
}

void Game::dialogueEnd(bool isMission)
{
    player_->changeTalking(false);
    if (isMission) {
        missionsPanel_->dialogueEnd();
    }
}


void Game::initOptionsState()
{
    optionsState = new OptionsState(this);
}

void Game::drawMap()
{ 

    SDL_Rect rectPanel = { minimapinfo_.xOrigin, minimapinfo_.yOrigin, 300, 150 };

    SDL_Rect src = { (int)lround((mCamera_->getCameraPosition().getX() - mCamera_->getWidth() * miniMapScale_ / 2 - player_->getWidth() / 2) / (getWindowWidth() / mCamera_->getWidth())),
                     (int)lround((mCamera_->getCameraPosition().getY() - mCamera_->getHeight() * miniMapScale_ / 2 - player_->getHeight() / 2) / (getWindowHeight() / mCamera_->getHeight())),
                     (int)lround(mCamera_->getWidth() * miniMapScale_),
                     (int)lround(mCamera_->getHeight() * miniMapScale_) };
    SDL_RenderCopy(renderer, background_, &src, &rectPanel);

    //Marco?
    Texture* selector_ = getTexture(minimapBorder);
    selector_->render(rectPanel);
    //background_->render(rectPanel);

    if (isMapPointerPut) 
        mapPoint->draw();

    pIcon->draw();
}

void Game::scalePoint()
{
    //BALIZA
    int smallDimension = 12;
    int offset = smallDimension / 2;
    mapPoint->setDimension(smallDimension, smallDimension);

    int posMinMiniMapX = (int)lround((mCamera_->getCameraPosition().getX() -
        mCamera_->getWidth() * miniMapScale_ / 2 - player_->getWidth() / 2) / (getWindowWidth() / mCamera_->getWidth()));
    int posMinMiniMapY = (int)lround((mCamera_->getCameraPosition().getY() - 
        mCamera_->getHeight() * miniMapScale_ / 2 - player_->getHeight() / 2) / (getWindowHeight() / mCamera_->getHeight()));
    int tamW = (int)lround(mCamera_->getWidth() * miniMapScale_);
    int tamH = (int)lround(mCamera_->getHeight() * miniMapScale_);

   /* double x = minimapinfo_.xOrigin + (mapPoint->getX() * (minimapinfo_.w / getWindowWidth()) - offset);
    double y = minimapinfo_.yOrigin + (mapPoint->getY() * (minimapinfo_.h / getWindowHeight()) - offset);*/

    double x = minimapinfo_.xOrigin + minimapinfo_.w / 2 + (mapPoint->getX() * (minimapinfo_.w / getWindowWidth())) - offset / 2;
    double y = minimapinfo_.yOrigin + minimapinfo_.h / 2 + (mapPoint->getY() * (minimapinfo_.h / getWindowHeight()));
    bool aux=false;
    if ((int)x<posMinMiniMapX || (int)x>posMinMiniMapX + tamW) aux = true;
    else if ((int)y<posMinMiniMapY || (int)y>posMinMiniMapY + tamH) aux = true;

    mapPoint->setPosition(x, y);

   /* if (aux) {
        mapPoint->setPosition(x, y);
    }
    else mapPoint->setPosition(x, y);*/
}

void Game::scalePlayerIcon(){
    //PLAYER
    int smallDimension = 20;
    int offset = smallDimension / 2;

    pIcon->setDimension(smallDimension, smallDimension);

    double x = minimapinfo_.xOrigin + minimapinfo_.w / 2 - offset / 2;
    double y = minimapinfo_.yOrigin + minimapinfo_.h / 2;

    pIcon->setPosition(x, y);
}

// Añadir pico después de las misiones
void Game::addPickaxe(int level)
{
    player_->addPickaxe(level);
}