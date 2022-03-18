#include "../../tmxlite-1.2.1/include/tmxlite/Map.hpp"
#include "../../tmxlite-1.2.1/include/tmxlite/Layer.hpp"
#include "../../tmxlite-1.2.1/include/tmxlite/TileLayer.hpp"
#include "../../tmxlite-1.2.1/include/tmxlite/ObjectGroup.hpp"
#include "../../tmxlite-1.2.1/include/tmxlite/Tileset.hpp"
#include "Game.h"

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false)
{    
    font_ = new Font("../Images/TheMoon.ttf", 50);
    animationManager = new AnimationManager(this);
    
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
    delete animationManager;
    delete savedState;
    delete shop_;
}

string Game::getGameName() {
    return name;
}

void Game::add(GameObject* gameObject) {//a�adir gO al vector
    gameObjects_.push_back(gameObject);
}

void Game::start()
{
    //loadMap("1.level");
    
    //loadMap("./Src/TilemapSrc/MainMap.tmx");
    //loadMap("C:/Users/Eli Todd/Documents/2º DESARROLLO DE VIDEOJUEGOS/Proyectos 2/MonkeyDelivery/MonkeyDelivery/Src/TilemapSrc/zona_shelter.tmx");
    //string route_ = "../resources/tilemap/zona_shelter.tmx";
    
    //string ayuda = "CarlosLeonAyudame";
    //std::string ayuda;

    mapInfo_.path_ = "..\\..\\resources\\tilemap\\zona_shelter.tmx";
    //mapInfo_.path_ = "..\\..\\..\\resources\\tilemap\\zona_shelter.tmx";
    loadMap(mapInfo_.path_);

    animationManager = new AnimationManager(this);

    player_ = new Player(this,animationManager); //Creacion del jugador
   
    //iE_ = new InteractiveEntity(this, tucanTexture, 500, 80);
    //add(iE_);

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_); 
    add (new IntectuableShop(this, 200, 200));
    enemiesCreation();//creacion de enemigos
    

    //missions_ = new MissionManager(this);
    shop_ = new Shop(player_, this);

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

    drawMap();
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

//Normal draw for entities(no Tiles)
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

//Draw de Tiles
void Game::drawTiles(tileObject o)
{
    
    SDL_Rect dest = o.getDest();
    SDL_Rect src = o.getSource();
    SDL_RenderCopyEx(renderer, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
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
    addEnemies(new Cat(this, 50, Point2D<int>(100, 100),animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(200, 80), 7,animationManager));
    addEnemies(new Bull(this, 35, Point2D<int>(350, 70),animationManager));
    addEnemies(new Scorpion(this, 80, Point2D<int>(100, 100), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(200, 100), animationManager));
}

void Game::scare(double scariness)
{
    player_->getScared(scariness);
}

void Game::interactDialogue()
{
    dialogueBox_->interact();
}

//TILEMAP
void Game::loadMap(string const &filename) {

    mapInfo_.tile_map = new tmx::Map();
    mapInfo_.tile_map->load(filename);
    
    // obtenemos el tamaño del mapa (en tiles)
    auto map_dimensions = mapInfo_.tile_map->getTileCount();
    mapInfo_.rows = map_dimensions.y;
    mapInfo_.cols = map_dimensions.x;

    // calculamos las dimensiones de los tiles
    auto tilesize = mapInfo_.tile_map->getTileSize();
    mapInfo_.tile_width = tilesize.x;
    mapInfo_.tile_height = tilesize.y;

    //convertir a textura
    auto rend = renderer;
    int bgWidth = mapInfo_.tile_width * mapInfo_.cols;
    int bgHeight = mapInfo_.tile_height * mapInfo_.rows;
    SDL_Texture* background = SDL_CreateTexture(rend,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        bgWidth,
        bgHeight
    );
        //SDL_SetTextureBlendMode(fondo, SDL_BLENDMODE_BLEND);
        //SDL_SetRenderTarget(renderer, fondo);

    //Establecemos los bordes de la camara con respecto al tamaño del tilemap
        //Camera::mainCamera->setBounds(0, 0, mapInfo_.cols * mapInfo_.tile_width, mapInfo_.rows * mapInfo_.tile_height);

    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    // (el mapa utiliza el �ndice [gid] del primer tile cargado del tileset como clave)
    // (para poder cargar los tilesets del archivo .tmx, les ponemos de nombre 
    // el nombre del archivo sin extension en el .json) 
      /*  auto& mapTilesets = mapInfo_.tile_map->getTilesets();
        for (auto& tileset : mapTilesets) {
            string name = tileset.getName();
            Texture* texture = &sdlutils().tilesets().find(name)->second;
            mapInfo_.tilesets.insert(pair<uint, Texture*>(tileset.getFirstGID(), texture));
        }*/

    // recorremos cada una de las capas (de momento solo las de tiles) del mapa
    auto& map_layers = mapInfo_.tile_map->getLayers();
    for (auto& layer : map_layers) {
        // aqui comprobamos que sea la capa de tiles
        if (layer->getType() == tmx::Layer::Type::Tile) {
            // cargamos la capa
            tmx::TileLayer* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());

            // obtenemos sus tiles
            auto& layer_tiles = tile_layer->getTiles();

            // recorremos todos los tiles para obtener su informacion
            for (auto y = 0; y < mapInfo_.rows; ++y) {
                for (auto x = 0; x < mapInfo_.cols; ++x) {
                    // obtenemos el indice relativo del tile en el mapa de tiles
                    auto tile_index = x + (y * mapInfo_.rows);

                    // con dicho indice obtenemos el indice del tile dentro de su tileset
                    auto cur_gid = layer_tiles[tile_index].ID;

                    // si es 0 esta vacio asi que continuamos a la siguiente iteracion
                    if (cur_gid == 0)
                        continue;

                    // guardamos el tileset que utiliza este tile (nos quedamos con el tileset cuyo gid sea
                    // el mas cercano, y a la vez menor, al gid del tile)
                    auto tset_gid = -1, tsx_file = 0;;
                    for (auto& ts : mapInfo_.tilesets) {
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
                    SDL_QueryTexture(mapInfo_.tilesets[tset_gid]->getTexture(),
                        NULL, NULL, &ts_width, &ts_height);

                    // calculamos el area del tileset que corresponde al dibujo del tile
                    auto region_x = (cur_gid % (ts_width / mapInfo_.tile_width)) * mapInfo_.tile_width;
                    auto region_y = (cur_gid / (ts_width / mapInfo_.tile_height)) * mapInfo_.tile_height;

                    // calculamos la posicion del tile
                    auto x_pos = x * mapInfo_.tile_width;
                    auto y_pos = y * mapInfo_.tile_height;

                    // metemos el tile
                    auto tileTex = mapInfo_.tilesets[tset_gid];

                    SDL_Rect src;
                    src.x = region_x; src.y = region_y;
                    src.w = mapInfo_.tile_width;
                    src.h = mapInfo_.tile_height;

                    SDL_Rect dest;
                    dest.x = x_pos;
                    dest.y = y_pos;
                    dest.w = src.w;
                    dest.h = src.h;

                    mapInfo_.tilesets[tset_gid]->render(src, dest);
                }
            }
        }
    }

    /*std::cout << "Started Loading \n";
    int current, mx, my, mw, mh;
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Failed to open map file." << endl;
        return;
    }
    in >> mw;
    in >> mh;
    in >> mx;
    in >> my;
    for (int i = 0; i < mh; i++) {
        for (int j = 0; j < mw; j++) {
            if (in.eof()) {
                cout << "Reached end of map file too soon." << endl;
                return;
            }
            in >> current;
            if (current != 0) {
                tileObject tmp;
                tmp.setImage("../TilemapSrc/Spritesheets/TilesetFloor.png", renderer);
                tmp.setSource((current - 1) * 32, 0, 32, 32);
                tmp.setDest((j * TILE_SIZE) + mx, (i * TILE_SIZE) + my, TILE_SIZE, TILE_SIZE);
                if (current == 2 || current == 4) tmp.setSolid(0);
                map.push_back(tmp);
            }
        }
    }
    in.close();*/
}

void Game::drawMap() {
    for (int i = 0; i < map.size(); i++) {
        drawTiles(map[i]);
    }
}